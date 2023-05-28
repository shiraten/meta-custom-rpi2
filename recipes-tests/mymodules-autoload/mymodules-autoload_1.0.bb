SUMMARY = "add module to be loaded at boot"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
PR = "r0"

SRC_URI = " \
	file://mymodules.conf \
"

# create /etc/modules-load.d/mymodules.conf to load module at boot
do_install() {
        install -d ${D}${base_prefix}/etc/modules-load.d/
        install -m 0755 ${WORKDIR}/mymodules.conf ${D}${base_prefix}/etc/modules-load.d/
}

FILES_${PN} += "${base_prefix}/etc/modules-load.d/"