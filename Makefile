ROOTFS=rootfs

initrd:
	@ if [ -d "${ROOTFS}" ]; then \
 		rm -r ${ROOTFS}; \
	fi
	@echo "Creating initrd"
	@mkdir -p $(ROOTFS) $(ROOTFS)/bin $(ROOTFS)/sbin $(ROOTFS)/etc $(ROOTFS)/lib $(ROOTFS)/lib64 $(ROOTFS)/var $(ROOTFS)/dev $(ROOTFS)/proc $(ROOTFS)/sys $(ROOTFS)/run $(ROOTFS)/tmp
