SUMMARY = "MPU9250 Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
inherit module
PR = "r0"

SRC_URI = " \
	file://mpu9250.h \
	file://mpu9250.c \
	file://Makefile \
"

S = "${WORKDIR}"

RPROVIDES_${PN} += "kernel-module-mpu9250"
