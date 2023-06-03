#include <linux/init.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of_device.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/delay.h>
#include <linux/kmod.h>
#include <linux/types.h>

#include <linux/slab.h>		// kmalloc
#include <linux/fs.h>		// file structure (filp_open)
#include <linux/moduleparam.h>	// use command line arguments (eg : insmod mymodule myvariable=5)
#include <linux/string.h>
#include <linux/ioctl.h>

#include "mpu9250.h"

#define I2C_BUS_AVAILABLE   (          1 )              // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME   ( "mpu9250" )              // Device and Driver Name
#define MPU9250_SLAVE_ADDR  (       0x68 )              // MPU9250 Slave Address
 
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

static int i2c_read_regs(struct i2c_client *client, u8 *cmd, u8 len, u8 *buf, u8 out_len)
{
	int ret;
	/* structure du message à envoyer */
	struct i2c_msg msg[2] = {
	{
		.addr = client->addr,
		.flags = 0,		// write
		.len = len,
		.buf = cmd,
	},
	{
		.addr = client->addr,
		.flags = I2C_M_RD,	// read
		.len = out_len,
		.buf = buf,
	}
	};

	/* on envoi le message et on lit le retour */
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0) {
		pr_debug("cannot transfer\n");
		dev_err(&client->dev, "I2C read failed\n");
		return ret;
	}

	return 0;
}

static int mpu9250_whoami(struct i2c_client *client, uint8_t *dest) {
	uint8_t cmd[1];
	uint8_t data[1];

	cmd[0] = MPU9250_FIFO_WHO_AM_I;
	i2c_read_regs(client, cmd, 1, data, 1);

	*dest = data[0];

	return 0;
}

static int mpu9250_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;
	uint8_t value[1];
	const void *match;
	enum inv_devices chip_type;
	const char *name;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EOPNOTSUPP;

	match = device_get_match_data(&client->dev);
	if (match) {
		chip_type = (enum inv_devices)match;
		name = client->name;
	} else if (id) {
		chip_type = (enum inv_devices)
			id->driver_data;
		name = id->name;
	} else {
		return -ENOSYS;
	}
	ret = mpu9250_whoami(client, value);
	pr_info("i2c read byte = 0x%x\n", *value);
	if (ret < 0)
		return ret;
    pr_info("mpu9250_probe finished\n");
	return 0;
}

/* remove is static void for raspi3 ? */
static int mpu9250_remove(struct i2c_client *client)
{
	pr_info("mpu9250_remove called\n");
	return 0;
}

module_i2c_driver(mpu9250_driver);

MODULE_AUTHOR("Maxime Duchene");
MODULE_DESCRIPTION("mpu9250 module");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
