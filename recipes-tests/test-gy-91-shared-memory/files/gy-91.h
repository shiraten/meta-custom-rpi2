#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#include <fcntl.h>      /* open */ 
#include <unistd.h>     /* exit */
#include <sys/ioctl.h>  /* ioctl */
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/select.h>

#define GET_IMU_WIA				300
#define GET_ACCEL_DATA				307
#define IMU_PWR_MGMT_1				309
#define IMU_PWR_MGMT_2				310

struct accel_data {
    int16_t x;
    int16_t y;
    int16_t z;
};

void initMPU9250(int mpu_file);
void readAccelData(int mpu_file, struct accel_data *accel_data);
