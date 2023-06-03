// check mpu6050 driver here :
// /home/maxime/Yocto-lab/build-rpi/tmp/work-shared/raspberrypi2/kernel-source/drivers/iio/imu/inv_mpu6050/inv_mpu_i2c.c

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/of_device.h>

#define MPU9250_FIFO_WHO_AM_I                    0x75

static int mpu9250_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int mpu9250_remove(struct i2c_client *client);
static int i2c_read_regs(struct i2c_client *client, u8 *cmd, u8 len, u8 *buf, u8 out_len);
static int mpu9250_whoami(struct i2c_client *client, const struct i2c_device_id *id);

/* i2c driver structure
/ check https://www.kernel.org/doc/Documentation/i2c/writing-clients */
static const struct i2c_device_id mpu9250_idtable[] = {
	{"mpu9250", 0},
	{}
};

/* define of_device_id to match corresponding node in dts file */
static const struct of_device_id mpu9250_of_match[] = {
    {.compatible = "inven,mpu9250"},
    {}
};
MODULE_DEVICE_TABLE(of, mpu9250_of_match);

static int mpu9250_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    pr_info("mpu9250_probe\n");
    const struct of_device_id *match;
    match = of_match_device(mpu9250_of_match, &client->dev);
    if (match) {
        pr_info("it's a match !");
    } else {
        pr_info("it's not a match !");
    }
    mpu9250_whoami(client, id);
    return 0;
}

static int mpu9250_remove(struct i2c_client *client) {
    pr_info("mpu9250_remove\n");
    return 0;
}

static struct i2c_driver mpu9250_driver = {
	.driver    = {
        .owner = THIS_MODULE,
		.name  = "mpu9250",
        .of_match_table = of_match_ptr(mpu9250_of_match),
	},
	.id_table  = mpu9250_idtable,
	.probe     = mpu9250_probe,
	.remove    = mpu9250_remove,
};

module_i2c_driver(mpu9250_driver);



static int i2c_read_regs(struct i2c_client *client, u8 *cmd, u8 len, u8 *buf, u8 out_len)
{
	int ret;
	/* structure du message à envoyer */
	struct i2c_msg msg[2] = {
	{
		.addr = client->addr,  /* slave address*/
		.flags = 0,  /* write */
		.len = len,  /* msg lenght */
		.buf = cmd,  /* register addr */
	},
	{
		.addr = client->addr,  /* slave address*/
		.flags = I2C_M_RD,	/* read */
		.len = out_len,  /* msg lenght */
		.buf = buf,  /* value read at register addr */
	}
	};

	/* send message and read answer */
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0) {
		pr_debug("cannot transfer\n");
		dev_err(&client->dev, "I2C read failed\n");
		return ret;
	}

	return 0;
}

static int mpu9250_whoami(struct i2c_client *client, const struct i2c_device_id *id) {
	uint8_t cmd;  /* register addr*/
	uint8_t data;  /* value read at register addr */

	cmd = MPU9250_FIFO_WHO_AM_I;
	i2c_read_regs(client, &cmd, 1, &data, 1);

    pr_info("%d", data);

	return 0;
}




MODULE_AUTHOR("Max D");
MODULE_DESCRIPTION("MPU9250 driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
