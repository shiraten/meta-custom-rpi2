

//This is a simple example of using IOCTL in a Linux device driver. If you want to send multiple arguments, put those variables into the structure, and pass the address of the structure.

#include "gy-91.h"

void initMPU9250(int mpu_file) {
	uint8_t c;
	// wake up device
	ioctl(mpu_file, IMU_PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors 
	usleep(100000); // Wait for all registers to reset 

	// // get stable time source
	// ioctl(mpu_file, IMU_PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
	// usleep(200000); 

	// // Configure Gyro and Thermometer
	// // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively; 
	// // minimum sleep time for this setting is 5.9 ms, which means sensor fusion update rates cannot
	// // be higher than 1 / 0.0059 = 170 Hz
	// // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
	// // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
	// ioctl(mpu_file, IMU_CONFIG, 0x03);  // set DLP_CFG to 3 to get 1Khz sample rate on gyroscope

	// // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
	// ioctl(mpu_file, IMU_SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; a rate consistent with the filter update rate 
	// 	                    // determined inset in CONFIG above

	// // Set gyroscope full scale range
	// // Range selects FS_SEL and GFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
	// ioctl(mpu_file, GET_GYRO_CONFIG, &c); // get current GYRO_CONFIG register value
	// // c = c & ~0xE0; // Clear self-test bits [7:5] 
	// c = c & ~0x03; // Clear Fchoice bits [1:0] 
	// c = c & ~0x18; // Clear GFS bits [4:3] -> 250dps
	// c = c | Gscale << 3; // Set full scale range for the gyro
	// //c = c | 0x03; // set fchoice[1:0] to 11, then in IMU_CONFIG, set DLP_CFG to 3 to get 1Khz | BW = 41Hz sample rate on gyroscope
	// ioctl(mpu_file, SET_GYRO_CONFIG, c); // Write new GYRO_CONFIG value to register

	// // Set accelerometer full-scale range configuration
	// ioctl(mpu_file, GET_ACCEL_CONFIG, &c); // get current ACCEL_CONFIG register value
	// // c = c & ~0xE0; // Clear self-test bits [7:5] 
	// c = c & ~0x18;  // Clear AFS bits [4:3]
	// c = c | Ascale << 3; // Set full scale range for the accelerometer 
	// ioctl(mpu_file, SET_ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value

	// // Set accelerometer sample rate configuration
	// // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
	// // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
	// ioctl(mpu_file, GET_ACCEL_CONFIG2, &c); // get current ACCEL_CONFIG2 register value
	// c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])  
	// c = c | 0x03;  // set fchoice to 1 and set accelerometer rate to 1 kHz and bandwidth to 41 Hz
	// ioctl(mpu_file, SET_ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value
	// // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates, 
	// // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

	// // Configure Interrupts and Bypass Enable
	// // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
	// // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips 
	// // can join the I2C bus and all can be controlled by the Arduino as master
	// ioctl(mpu_file, IMU_INT_PIN_CFG, 0x20);	// disable bypass
	// ioctl(mpu_file, IMU_INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
	// usleep(100000);
}

void readAccelData(int mpu_file, struct accel_data *accel_data) {
	uint8_t data[6];
	int i;
	ioctl(mpu_file, GET_ACCEL_DATA, data);
	accel_data->x = ((int16_t)data[0] << 8) | data[1];
	accel_data->y = ((int16_t)data[2] << 8) | data[3];
	accel_data->z = ((int16_t)data[4] << 8) | data[5];
}

int main(int argc, char *argv[])
{
	int mpu_file;		// ioctl mpu_file
	int ret;
    struct accel_data accel_data;
// setup
    mpu_file = open("/dev/mpu9250_device", O_RDWR);    // open file corresponding to mpu driver
	if(mpu_file < 0) {
			printf("Cannot open device file...\n");
			return 0;
	}

// MPU9250 IMU
    uint8_t c;
    ioctl(mpu_file, GET_IMU_WIA, (uint8_t *) &c);  // Read WHO_AM_I register for MPU9250
    printf("MPU9250 ID read is %02X\n", c);
    if (c != 0x73) // WHO_AM_I should always be 0x73
    {
        printf("Could not connect to MPU9250: ID read is %02X instead of 0x73\n", c);
        return (-1);
    }
    printf("MPU9250 is online...\n");


    initMPU9250(mpu_file);
	readAccelData(mpu_file, &accel_data);
    printf("accel X %04X\n", accel_data.x);
    printf("accel Y %04X\n", accel_data.y);
    printf("accel Z %04X\n", accel_data.z);

	close(mpu_file);

    return 0;
}
