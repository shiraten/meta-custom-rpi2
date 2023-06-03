FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://0001-add-mpu9250-and-bmp280-to-dts.patch \
    "
