# We base this recipe on core-image-minimal core image
require recipes-core/images/rpi-test-image.bb

# Adding a description is optional but often helps the user understand the purpose of the image
DESCRIPTION = "This is a customized version of the crpi-test-image image available in meta-raspberrypi"

# We specify here the additional recipes to be added to the build
IMAGE_INSTALL += " \
    hello-world \
    blink-test \
    pwm-test \
    nano \
    ldd-hello-world \
    mymodules-autoload \
    "
