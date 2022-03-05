ROOTFS=$(shell pwd)/rootfs
LINUX=$(shell pwd)/linux
OVERLAY=$(shell pwd)/overlay
LIBC=$(shell pwd)/libc
OUTPUT=$(shell pwd)
LINUX_VERSION=5.16.12
LINUX_MAJOR=5
LIBC_VERSION=2.34

initrd: root kernel libc apps
	cp -rf $(OVERLAY)/* $(ROOTFS)
	cd $(ROOTFS) && ln -s "./bin/init" "./init"
	cd $(ROOTFS) && chmod -R 777 .
	cd $(ROOTFS) && find . | cpio -R root:root -H newc -o > "${OUTPUT}/initrd.img"

apps:
	$(MAKE) -C $(OUTPUT)/src

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
	$(MAKE) -C ${LINUX}/src/linux-$(LINUX_VERSION)/ -j$(shell nproc)

.PHONY: libc
libc:
	@ echo "Downloading libc $(LIBC_VERSION)"
	mkdir -p $(LIBC) $(LIBC)/src
	wget -nc https://ftp.gnu.org/gnu/glibc/glibc-$(LIBC_VERSION).tar.xz -P $(LIBC)
	@ if ! [ -d "${LIBC}/src/glibc-$(LIBC_VERSION)" ]; then \
		tar -xf $(LIBC)/glibc-$(LIBC_VERSION).tar.xz -C $(LIBC)/src/; \
	fi
	@ if ! [ -d "$(LIBC)/src/glibc-$(LIBC_VERSION)/build" ]; then \
		cd $(LIBC)/src/glibc-$(LIBC_VERSION)/ && mkdir build && cd build && ../configure --disable-timezone-tools --disable-build-nscd --disable-nscd --enable-kernel=3.2 --prefix="/usr/"; \
	fi
	$(MAKE) -C $(LIBC)/src/glibc-$(LIBC_VERSION)/build -j$(shell nproc)
	$(MAKE) -C $(LIBC)/src/glibc-$(LIBC_VERSION)/build DESTDIR=$(ROOTFS) install -j$(shell nproc)

clean:
	rm -rf $(ROOTFS) $(LINUX) $(LIBC)
	
run: initrd
	qemu-system-x86_64 -kernel ${LINUX}/src/linux-$(LINUX_VERSION)/arch/x86/boot/bzImage -initrd $(OUTPUT)/initrd.img -m 512M