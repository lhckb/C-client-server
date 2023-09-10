### Basic Linux Kernel Driver
This driver simply prints a message into the Kernel Buffer.
It is not a static driver, which means it can be linked to the kernel as a module.
In order to build it on your own machine, make sure you have the correct Kernel Headers. In case you dont, simply `sudo apt install linux-headers-$(uname -r)` on Debian-based systems.

To build the Kernel Object, type `make`.

To install the module, type `sudo insmod hello_driver.ko`.
To uninstall the module, type `sudo rmmod hello_driver`.
To verify if the installation was successful, `lsmod | grep hello` and there should be an output.
To verufy the messages printed to the Kernel Buffer, type `sudo dmesg`.