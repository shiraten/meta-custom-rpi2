DESCRIPTION = "Storage Performance Dev kit"
HOMEPAGE = "https://spdk.io/"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://www.github.com/spdk/spdk.git;protocol=https;branch=master;name=commit"
SRCREV_commit = "2d355b3a1c8f641b32d8ea154a55b9b5308586c4"

# do_configure_prepend() {
#     ./configure --with-dpdk="" --with-nvme-cuse --with-fio="" --without-vhost --with-rdma --with-shared --disable-tests --disable-unit-tests --enable-debug
# }

# do_compile() {
#     make
# }

# do_install() {
#     make install
# }
