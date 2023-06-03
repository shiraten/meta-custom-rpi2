SUMMARY = "GY-91 test code"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
PR = "r0"

SRC_URI = " \
	file://test-gy-91.c \
	file://gy-91.h \
"

TARGET_CC_ARCH += "${LDFLAGS}"

S = "${WORKDIR}"

do_compile() {
	${CC} test-gy-91.c -o test-gy-91
}

# Install binary to final directory /usr/bin
do_install() {
        install -d ${D}${bindir}
        install -m 0755 ${S}/test-gy-91 ${D}${bindir}
}