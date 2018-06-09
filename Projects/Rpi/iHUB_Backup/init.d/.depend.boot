TARGETS = fake-hwclock mountkernfs.sh hostname.sh udev keyboard-setup mountdevsubfs.sh hdparm checkroot.sh console-setup mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh networking alsa-utils x11-common kbd urandom kmod udev-finish bootmisc.sh plymouth-log raspi-config procps checkroot-bootclean.sh checkfs.sh
INTERACTIVE = udev keyboard-setup checkroot.sh console-setup kbd checkfs.sh
udev: mountkernfs.sh
keyboard-setup: mountkernfs.sh udev
mountdevsubfs.sh: mountkernfs.sh udev
hdparm: mountdevsubfs.sh udev
checkroot.sh: fake-hwclock mountdevsubfs.sh hostname.sh hdparm keyboard-setup
console-setup: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh kbd
mountall.sh: checkfs.sh checkroot-bootclean.sh
mountall-bootclean.sh: mountall.sh
mountnfs.sh: mountall.sh mountall-bootclean.sh networking
mountnfs-bootclean.sh: mountall.sh mountall-bootclean.sh mountnfs.sh
networking: mountkernfs.sh mountall.sh mountall-bootclean.sh urandom procps
alsa-utils: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh
x11-common: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh
kbd: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh
urandom: mountall.sh mountall-bootclean.sh
kmod: checkroot.sh
udev-finish: udev mountall.sh mountall-bootclean.sh
bootmisc.sh: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh udev checkroot-bootclean.sh
plymouth-log: mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh
raspi-config: udev mountkernfs.sh mountall.sh mountall-bootclean.sh mountnfs.sh mountnfs-bootclean.sh
procps: mountkernfs.sh mountall.sh mountall-bootclean.sh udev
checkroot-bootclean.sh: checkroot.sh
checkfs.sh: checkroot.sh
