#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include <security/pam_modules.h>

// Replace with your numwork's serial number
#define myNumWorksSerial "KABCABFRMTUxNzky"

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{

    if (argc == 0) {
        fprintf(stdout, "ERROR: Missing serial number in pam.d rules for current application !");
        return PAM_AUTH_ERR;
    }

    libusb_device_handle *device = NULL;
    int status = libusb_init(NULL);
    if (status != 0)
    {
        fprintf(stderr, "Failed to init libusb\n");
        return PAM_AUTH_ERR;
    }

    fprintf(stdout, "Waiting (for eternity) for a device ...\n");
    fflush(stdout);

    while (device == NULL)
    {
        device = libusb_open_device_with_vid_pid(NULL, 0x0483, 0xa291);
        sleep(1);
    }

    unsigned char serial[20];
    struct libusb_device_descriptor desc;
    libusb_device *dev = libusb_get_device(device);
    int result = libusb_get_device_descriptor(dev, &desc);
    if (result < 0)
    {
        fprintf(stderr, "Couldn't get device descriptor!\n");
        libusb_close(device);
        libusb_exit(NULL);
        return PAM_AUTH_ERR;
    }

    int r = libusb_get_string_descriptor_ascii(device, desc.iSerialNumber, serial, 20);
    if (r < 0)
    {
        fprintf(stderr, "Couldn't get serial number!\n");
        libusb_close(device);
        libusb_exit(NULL);
        return PAM_AUTH_ERR;
    }

    if (strcmp(serial, argv[0]) == 0)
    {
        libusb_close(device);
        libusb_exit(NULL);
        fprintf(stdout,"Success!\n");
        return PAM_SUCCESS;
    }
    else
    {
        fprintf(stderr, "This is not my numworks !\n");
        libusb_close(device);
        libusb_exit(NULL);
        return PAM_PERM_DENIED;
    }
}
