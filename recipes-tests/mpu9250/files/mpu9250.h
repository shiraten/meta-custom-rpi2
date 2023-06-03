/**
 * InvenSense MPU9250 Register Map.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MPU9250_REG_H_INCLUDED
#define MPU9250_REG_H_INCLUDED

enum inv_devices {
    INV_MPU9250,
};

#define MPU9250_I2C_CLOCK_SPEED                  400000UL // I2C is 400KHz max
#define MPU9250_I2C_ADDRESS                      0x68 // This address is used by MPU9250 when ADC0 pin is logic low
#define MPU9250_I2C_ADDRESS_ALT                  0x69 // This address is used by MPU9250 when ADC0 pin is logic high

// Note, this is the reset value for all registers except 
// - Register 107 (value = 0x01) Power Management 1
// - Register 117 (value = 0x73) WHO_AM_I
#define MPU9250_REG_RESET                        0x00

// From section 7.5 SPI Interface
// SPI read and write operations are completed in 16 or more clock cycles (two or more bytes). The
// first byte contains the SPI A ddress, and the following byte(s) contain(s) the SPI data. The first
// bit of the first byte contains the Read/Write bit and indicates the Read (1) or Write (0) operation.
// The following 7 bits contain the Register Address. In cases of multiple-byte Read/Writes, data is
// two or more bytes...
#define MPU9250_READ_MASK                        0x80

// Self Test, Gyro
#define MPU9250_SELF_TEST_X_GYRO                 0x00
#define MPU9250_SELF_TEST_Y_GYRO                 0x01
#define MPU9250_SELF_TEST_Z_GYRO                 0x02



// Self Test, Accelerometer
#define MPU9250_SELF_TEST_X_ACCEL                0x0d
#define MPU9250_SELF_TEST_Y_ACCEL                0x0e
#define MPU9250_SELF_TEST_Z_ACCEL                0x0f

 // Gyro Offset
#define MPU9250_XG_OFFSET_H                      0x13
#define MPU9250_XG_OFFSET_L                      0x14
#define MPU9250_YG_OFFSET_H                      0x15
#define MPU9250_YG_OFFSET_L                      0x16
#define MPU9250_ZG_OFFSET_H                      0x17
#define MPU9250_ZG_OFFSET_L                      0x18


#define MPU9250_SMPLRT_DIV                       0x19

// Config
#define MPU9250_CONFIG                           0x1a
#define MPU9250_GYRO_CONFIG                      0x1b
#define MPU9250_ACCEL_CONFIG                     0x1c
#define MPU9250_ACCEL_CONFIG_2                   0x1d
#define MPU9250_LP_ACCEL_ODR                     0x1e

#define MPU9250_WOM_THR                          0x1f

#define MPU9250_FIFO_EN                          0x23

// I2C
#define MPU9250_I2C_MST_CTRL                     0x24
#define MPU9250_I2C_SLV0_ADDR                    0x25
#define MPU9250_I2C_SLV0_REG                     0x26
#define MPU9250_I2C_SLV0_CTRL                    0x27

#define MPU9250_I2C_SLV1_ADDR                    0x28
#define MPU9250_I2C_SLV1_REG                     0x29
#define MPU9250_I2C_SLV1_CTRL                    0x2a

#define MPU9250_I2C_SLV2_ADDR                    0x2b
#define MPU9250_I2C_SLV2_REG                     0x2c
#define MPU9250_I2C_SLV2_CTRL                    0x2d

#define MPU9250_I2C_SLV3_ADDR                    0x2e
#define MPU9250_I2C_SLV3_REG                     0x2f
#define MPU9250_I2C_SLV3_CTRL                    0x30

#define MPU9250_I2C_SLV4_ADDR                    0x31
#define MPU9250_I2C_SLV4_REG                     0x32
#define MPU9250_I2C_SLV4_DO                      0x33
#define MPU9250_I2C_SLV4_CTRL                    0x34
#define MPU9250_I2C_SLV4_DI                      0x35

#define MPU9250_I2C_MST_STATUS                   0x36

#define MPU9250_INT_PIN_CFG                      0x37
#define MPU9250_INT_ENABLE                       0x38

#define MPU9250_DMP_INT_STATUS                   0x39 // Check DMP Interrupt, see 0x6d

#define MPU9250_INT_STATUS                       0x3a

// Accel XOUT
#define MPU9250_ACCEL_XOUT_H                     0x3b
#define MPU9250_ACCEL_XOUT_L                     0x3c
#define MPU9250_ACCEL_YOUT_H                     0x3d
#define MPU9250_ACCEL_YOUT_L                     0x3e
#define MPU9250_ACCEL_ZOUT_H                     0x3f
#define MPU9250_ACCEL_ZOUT_L                     0x40

// Temp.
#define MPU9250_TEMP_OUT_H                       0x41
#define MPU9250_TEMP_OUT_L                       0x42

// Gyro.
#define MPU9250_GYRO_XOUT_H                      0x43
#define MPU9250_GYRO_XOUT_L                      0x44
#define MPU9250_GYRO_YOUT_H                      0x45
#define MPU9250_GYRO_YOUT_L                      0x46
#define MPU9250_GYRO_ZOUT_H                      0x47
#define MPU9250_GYRO_ZOUT_L                      0x48

// Ext. Sensor data
#define MPU9250_EXT_SENS_DATA_00                 0x49
#define MPU9250_EXT_SENS_DATA_01                 0x4a
#define MPU9250_EXT_SENS_DATA_02                 0x4b
#define MPU9250_EXT_SENS_DATA_03                 0x4c
#define MPU9250_EXT_SENS_DATA_04                 0x4d
#define MPU9250_EXT_SENS_DATA_05                 0x4e
#define MPU9250_EXT_SENS_DATA_06                 0x4f
#define MPU9250_EXT_SENS_DATA_07                 0x50
#define MPU9250_EXT_SENS_DATA_08                 0x51
#define MPU9250_EXT_SENS_DATA_09                 0x52
#define MPU9250_EXT_SENS_DATA_10                 0x53
#define MPU9250_EXT_SENS_DATA_11                 0x54
#define MPU9250_EXT_SENS_DATA_12                 0x55
#define MPU9250_EXT_SENS_DATA_13                 0x56
#define MPU9250_EXT_SENS_DATA_14                 0x57
#define MPU9250_EXT_SENS_DATA_15                 0x58
#define MPU9250_EXT_SENS_DATA_16                 0x59
#define MPU9250_EXT_SENS_DATA_17                 0x5a
#define MPU9250_EXT_SENS_DATA_18                 0x5b
#define MPU9250_EXT_SENS_DATA_19                 0x5c
#define MPU9250_EXT_SENS_DATA_20                 0x5d
#define MPU9250_EXT_SENS_DATA_21                 0x5e
#define MPU9250_EXT_SENS_DATA_22                 0x5f
#define MPU9250_EXT_SENS_DATA_23                 0x60

// I2C slave
#define MPU9250_I2C_SLV0_DO                      0x63
#define MPU9250_I2C_SLV1_DO                      0x64
#define MPU9250_I2C_SLV2_DO                      0x65
#define MPU9250_I2C_SLV3_DO                      0x66

#define MPU9250_I2C_MST_DELAY_CTRL               0x67


// Signal path
#define MPU9250_SIGNAL_PATH_RESET                0x68

// Motion detect
#define MPU9250_MOT_DETECT_CTRL                  0x69

// User
#define MPU9250_USER_CTRL                        0x6a // Bit 7 enable DMP, bit 3 reset DMP. See 0x6d

// Power management
#define MPU9250_PWR_MGMT_1                       0x6b
#define MPU9250_PWR_MGMT_2                       0x6c

// ...Looked for notes on DMP features, but Invensense docs were lacking.
// Found kriswiner's Arduino sketch for Basic AHRS, and found values/notes for
// Digital Motion Processing registers.
//
// See https://github.com/kriswiner/MPU-9250/blob/master/MPU9250BasicAHRS.ino
#define MPU9250_DMP_BANK                         0x6d
#define MPU9250_DMP_RW_PNT                       0x6e
#define MPU9250_DMP_REG                          0x6f
#define MPU9250_DMP_REG_1                        0x70
#define MPU9250_DMP_REG_2                        0x71

// FIFO Count
#define MPU9250_FIFO_COUNTH                      0x72
#define MPU9250_FIFO_COUNTL                      0x73
#define MPU9250_FIFO_R_W                         0x74
#define MPU9250_FIFO_WHO_AM_I                    0x75

// Accel. offset
#define MPU9250_XA_OFFSET_H                      0x77
#define MPU9250_XA_OFFSET_L                      0x78
#define MPU9250_YA_OFFSET_H                      0x7a
#define MPU9250_YA_OFFSET_L                      0x7b
#define MPU9250_ZA_OFFSET_H                      0x7d
#define MPU9250_ZA_OFFSET_L                      0x7e

// Read-only Reg
#define AK8963_I2C_ADDR             0x0C // slave address for the AK8963
#define AK8963_DEVICE_ID             0x48
#define AK8963_WIA                 0x00
#define AK8963_INFO                 0x01
#define AK8963_ST1                 0x02 // data ready status bit 0
#define AK8963_XOUT_L                 0x03 // data
#define AK8963_XOUT_H                 0x04
#define AK8963_YOUT_L                 0x05
#define AK8963_YOUT_H                 0x06
#define AK8963_ZOUT_L                 0x07
#define AK8963_ZOUT_H                 0x08
#define AK8963_ST2                 0x09 // Data overflow bit 3 and data read error status bit 2
#define AK8963_CNTL                 0x0A // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_ASTC                 0x0C // Self test control
#define AK8963_I2CDIS                 0x0F // I2C disable
#define AK8963_ASAX                 0x10 // Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY                 0x11 // Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ                 0x12 // Fuse ROM z-axis sensitivity adjustment value

// Write/Read Reg
#define AK8963_CNTL1                 0x0A
#define AK8963_CNTL2                 0x0B
#define AK8963_ASTC                 0x0C
#define AK8963_TS1                 0x0D
#define AK8963_TS2                 0x0E
#define AK8963_I2CDIS                 0x0F

// Commands ID
#define GET_IMU_WIA                300
#define GET_TEMPERATURE                301
#define SET_ACCEL_CONFIG            302
#define SET_ACCEL_CONFIG2            303
#define GET_ACCEL_CONFIG            304
#define GET_GYRO_CONFIG                305
#define SET_GYRO_CONFIG                306
#define GET_ACCEL_DATA                307
#define GET_GYRO_DATA                308
#define IMU_PWR_MGMT_1                309
#define IMU_PWR_MGMT_2                310
#define IMU_INT_ENABLE                311
#define IMU_FIFO_EN                312
#define IMU_I2C_MST_CTRL            313
#define IMU_USR_CTRL                314
#define IMU_CONFIG                315
#define IMU_SMPLRT_DIV                316
#define IMU_FIFO_COUNTH                317
#define IMU_XA_OFFSET_H                318
#define IMU_XA_OFFSET_L                319
#define IMU_YA_OFFSET_H                320
#define IMU_YA_OFFSET_L                321
#define IMU_ZA_OFFSET_H                322
#define IMU_ZA_OFFSET_L                323
#define IMU_XG_OFFSET_H                324
#define IMU_XG_OFFSET_L                325
#define IMU_YG_OFFSET_H                326
#define IMU_YG_OFFSET_L                327
#define IMU_ZG_OFFSET_H                328
#define IMU_ZG_OFFSET_L                329
#define IMU_GET_XA_OFFSET            330
#define IMU_GET_YA_OFFSET            331
#define IMU_GET_ZA_OFFSET            332
#define IMU_GET_FIFO_R_W            333
#define IMU_INT_PIN_CFG                334
#define GET_ACCEL_CONFIG2            335
#define IMU_INT_STATUS                336
#define IMU_SELF_TEST_X_ACCEL            337
#define IMU_SELF_TEST_Y_ACCEL            338
#define IMU_SELF_TEST_Z_ACCEL            339
#define IMU_SELF_TEST_X_GYRO            340
#define IMU_SELF_TEST_Y_GYRO            341
#define IMU_SELF_TEST_Z_GYRO            342

#define SLV0_CTRL                343
#define SLV0_ADDR                344
#define SLV0_REG                345
#define SLV0_D0                    346
#define SLV0_EXT_DATA_0                347

#endif
