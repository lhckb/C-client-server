cmd_/home/luis/low-level-programming/linux_drivers/Module.symvers := sed 's/\.ko$$/\.o/' /home/luis/low-level-programming/linux_drivers/modules.order | scripts/mod/modpost -m -a  -o /home/luis/low-level-programming/linux_drivers/Module.symvers -e -i Module.symvers   -T -
