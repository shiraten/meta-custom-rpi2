#include <linux/init.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of_device.h>
#include <linux/regmap.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/delay.h>
#include <linux/kmod.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

#include <linux/slab.h>        // kmalloc
#include <linux/fs.h>        // file structure (filp_open)
#include <linux/moduleparam.h>    // use command line arguments (eg : insmod mymodule myvariable=5)
#include <linux/string.h>
#include <linux/ioctl.h>

#include "mpu9250.h"

#define I2C_BUS_AVAILABLE 1             // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME "mpu9250"             // Device and Driver Name
#define MPU9250_SLAVE_ADDR 0x68              // MPU9250 Slave Address

dev_t dev = 0;
static struct class *dev_class;
static struct cdev mpu9250_cdev;

static struct mpu9250_data {
	struct i2c_client *client;
	const struct i2c_device_id *id;
} mpu9250;
 
static int mpu9250_probe(struct i2c_client *client, const struct i2c_device_id *id);
/* remove is static void for raspi3 ? */
static int mpu9250_remove(struct i2c_client *client);

/* define of_device_id to match corresponding node in dts file */
static const struct of_device_id mpu9250_of_match[] = {
    {
        .compatible = "inven,mpu9250",
        .data = (void *)INV_MPU9250
    },
    {}
};
MODULE_DEVICE_TABLE(of, mpu9250_of_match);

/*
** Structure that has slave device id
*/
static struct i2c_device_id mpu9250_idtable[] = {
      { SLAVE_DEVICE_NAME, INV_MPU9250},
      { }
};
MODULE_DEVICE_TABLE(i2c, mpu9250_idtable);

/*
** I2C driver Structure that has to be added to linux
*/
static struct i2c_driver mpu9250_driver = {
      .driver = {
            .name  = SLAVE_DEVICE_NAME,
            .owner = THIS_MODULE,
            .of_match_table = mpu9250_of_match,
      },

      .probe      = mpu9250_probe,
      .remove     = mpu9250_remove,
      .id_table   = mpu9250_idtable,
};

static const struct regmap_config mpu9250_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
};

struct regmap *regmap;

int data_lenght = 1;

static long int my_ioctl_function(struct file *file, unsigned int cmd, long unsigned int args)
{
    uint8_t ret = 0;
    pr_debug("[mpu9250]: my_ioctl_function\n");

    /* using a structure for args, we can then pass all value to the structure on a single commande GET_VALUE (OR GET ACCEL, GET_GYRO, etc.) */

    switch(cmd)
    {
        case GET_IMU_WIA:
            pr_info("GET_IMU_WIA\n");
            ret = regmap_read(regmap, MPU9250_FIFO_WHO_AM_I, (unsigned int *) args);
            break;
        case IMU_PWR_MGMT_1:
			pr_info("IMU_PWR_MGMT_1\n");
            ret = regmap_write(regmap, MPU9250_PWR_MGMT_1, (unsigned int) args);
			break;
		case IMU_PWR_MGMT_2:
			pr_info("IMU_PWR_MGMT_2\n");
            ret = regmap_write(regmap, MPU9250_PWR_MGMT_2, (unsigned int) args);
			break;
        case GET_ACCEL_DATA:
            pr_info("GET_ACCEL_DATA\n");
            ret = regmap_bulk_read(regmap, MPU9250_ACCEL_XOUT_H, &args, 6);
            break;
        case GET_ACCEL_DATA2:
            pr_info("GET_ACCEL_DATA2\n");
            ret = regmap_read(regmap, MPU9250_ACCEL_XOUT_H, (unsigned int *) args);
            break;
        default : 
            pr_info("default\n");
            ret = -EINVAL;
            break;
    }
    return ret;
}

/* accès a la fonction depuis l'espace utilisateur */
static struct file_operations fops = {
    .unlocked_ioctl = my_ioctl_function,
};

static int mpu9250_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret;
    unsigned int value;
    const void *match;
    enum inv_devices chip_type;
    const char *name;

    mpu9250.client = client;
	mpu9250.id = id;

    if (!i2c_check_functionality(mpu9250.client->adapter,
                     I2C_FUNC_SMBUS_I2C_BLOCK))
        return -EOPNOTSUPP;

    match = device_get_match_data(&mpu9250.client->dev);
    if (match) {
        chip_type = (enum inv_devices)match;
        name = mpu9250.client->name;
    } else if (id) {
        chip_type = (enum inv_devices)
            mpu9250.id->driver_data;
        name = mpu9250.id->name;
    } else {
        return -ENOSYS;
    }

    regmap = devm_regmap_init_i2c(client, &mpu9250_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		return PTR_ERR(regmap);
	}

    ret = regmap_read(regmap, MPU9250_FIFO_WHO_AM_I, &value);
    pr_info("i2c read byte = 0x%02X\n", value);
    if (ret < 0)
        return ret;

    /* only to check if regmap_bulk_read works, to be removed*/
    ret = regmap_bulk_read(regmap,
					       MPU9250_ACCEL_XOUT_H,
					       &thresh_data, 6);
    pr_info("i2c read byte = 0x%02lX\n", thresh_data);

    /* Allocating Major number */
    if((alloc_chrdev_region(&dev, 0, 1, "mpu9250_Dev")) <0){
            pr_err("Cannot allocate major number\n");
            return -1;
    }
    pr_info("Major = %d Minor = %d \n", MAJOR(dev), MINOR(dev));

    /* Creating cdev structure */
    cdev_init(&mpu9250_cdev,&fops);

    /* Adding character device to the system*/
    if((cdev_add(&mpu9250_cdev, dev, 1)) < 0){
        pr_err("Cannot add the device to the system\n");
        goto r_class;
    }

    /* Creating struct class */
    if(IS_ERR(dev_class = class_create(THIS_MODULE, "mpu9250_class"))){
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }

    /* Creating device */
    if(IS_ERR(device_create(dev_class, NULL, dev, NULL, "mpu9250_device"))){
        pr_err("Cannot create the Device 1\n");
        goto r_device;
    }

    pr_info("mpu9250_probe finished\n");
    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev,1);
    return -1;
}

static int mpu9250_remove(struct i2c_client *client)
{
    pr_info("mpu9250_remove called\n");
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&mpu9250_cdev);
    unregister_chrdev_region(dev, 1);
}

module_i2c_driver(mpu9250_driver);

MODULE_AUTHOR("Maxime Duchene");
MODULE_DESCRIPTION("mpu9250 module");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
