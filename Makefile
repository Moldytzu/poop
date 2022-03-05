ROOTFS=rootfs
LINUX=linux
LIBC=libc
LINUX_VERSION=5.16.12
LINUX_MAJOR=5
LIBC_VERSION=2.34

initrd: root kernel libc

root:
	@ if [ -d "${ROOTFS}" ]; then \
 		rm -r ${ROOTFS}; \
	fi
	@ echo "Creating root"
	mkdir -p $(ROOTFS) $(ROOTFS)/bin $(ROOTFS)/sbin $(ROOTFS)/etc $(ROOTFS)/lib $(ROOTFS)/lib64 $(ROOTFS)/var $(ROOTFS)/dev $(ROOTFS)/proc $(ROOTFS)/sys $(ROOTFS)/run $(ROOTFS)/tmp

kernel:
	@ echo "Downloading Linux $(LINUX_VERSION)"
	mkdir -p $(LINUX) $(LINUX)/src
	wget -nc https://cdn.kernel.org/pub/linux/kernel/v$(LINUX_MAJOR).x/linux-$(LINUX_VERSION).tar.xz -P $(LINUX)
	@ if ! [ -d "${LINUX}/src/linux-$(LINUX_VERSION)" ]; then \
		tar -xf $(LINUX)/linux-$(LINUX_VERSION).tar.xz -C $(LINUX)/src/; \
	fi
	@ if ! [ -f "${LINUX}/src/linux-$(LINUX_VERSION)/.config" ]; then \
		cd ${LINUX}/src/linux-$(LINUX_VERSION)/ && $(MAKE) defconfig; \
	fi
	cd ${LINUX}/src/linux-$(LINUX_VERSION)/ && $(MAKE) -j$(shell nproc)

libc:
	@ echo "Downloading libc $(LIBC_VERSION)"
	mkdir -p $(LIBC) $(LIBC)/src
	wget -nc https://ftp.gnu.org/gnu/glibc/glibc-$(LIBC_VERSION).tar.xz -P $(LIBC)

clean:
	rm -rf $(ROOTFS) $(LINUX)