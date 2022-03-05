ROOTFS=rootfs
LINUX=linux
LINUX_VERSION=5.16.12
LINUX_MAJOR=5

initrd: kernel
	@ if [ -d "${ROOTFS}" ]; then \
 		rm -r ${ROOTFS}; \
	fi
	@ echo "Creating initrd"
	mkdir -p $(ROOTFS) $(ROOTFS)/bin $(ROOTFS)/sbin $(ROOTFS)/etc $(ROOTFS)/lib $(ROOTFS)/lib64 $(ROOTFS)/var $(ROOTFS)/dev $(ROOTFS)/proc $(ROOTFS)/sys $(ROOTFS)/run $(ROOTFS)/tmp

kernel:
	@ echo "Downloading Linux $(LINUX_VERSION)"
	mkdir -p $(LINUX)
	wget -nc https://cdn.kernel.org/pub/linux/kernel/v$(LINUX_MAJOR).x/linux-$(LINUX_VERSION).tar.xz -P $(LINUX)

clean:
	rm -rf $(ROOTFS) $(LINUX)