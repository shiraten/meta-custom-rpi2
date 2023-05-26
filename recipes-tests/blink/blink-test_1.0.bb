# Package summary
SUMMARY = "Hello World"
# License, for example MIT
LICENSE = "MIT"
# License checksum file is always required
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "bcm2835"

# hello-world.c from local file
SRC_URI = "file://blink.c"

# Set LDFLAGS options provided by the build system
TARGET_CC_ARCH += "${LDFLAGS}"

# Change source directory to workdirectory where hello-world.c is
S = "${WORKDIR}"

# Compile hello-world from sources, no Makefile
do_compile() {
	${CC} blink.c -o test-blink -lbcm2835
}

# Install binary to final directory /usr/bin
do_install() {
        install -d ${D}${bindir}
        install -m 0755 ${S}/test-blink ${D}${bindir}
}
