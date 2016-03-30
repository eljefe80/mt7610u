#include config.mk

KDIR := /lib/modules/$(shell uname -r)/build

obj_wsc :=
obj_vht :=
obj_cmm := \
	crypt_md5.o\
        crypt_sha2.o\
        crypt_hmac.o\
        crypt_aes.o\
        crypt_arc4.o\
        mlme.o\
        cmm_wep.o\
        action.o\
        cmm_data.o\
	rtmp_init.o\
        rtmp_init_inf.o\
        cmm_tkip.o\
        cmm_aes.o\
        cmm_sync.o\
        eeprom.o\
        cmm_sanity.o\
        cmm_info.o\
        cmm_cfg.o\
        cmm_wpa.o\
        cmm_radar.o\
	spectrum.o\
        rtmp_timer.o\
        rt_channel.o\
        cmm_profile.o\
        cmm_asic.o\
        scan.o\
        cmm_cmd.o\
        uapsd.o\
	ps.o\
	ra_ctrl.o\
        alg_legacy.o\
        alg_ags.o\
	rtmp_chip.o\
		txpower.o\
	rtmp_mac.o\
	mgmt_hw.o\
	mgmt_entrytb.o\
        rtmp_phy.o\
        rlt_phy.o\
	rlt_rf.o

obj_cmm += netif_block.o

obj_cmm += alg_grp.o

obj_cmm += alg_ags.o

obj_cmm += cmm_dfs.o

obj_cmm += cmm_cs.o

obj_cmm += \
        ba_action.o\
        mgmt_ht.o

obj_cmm += \
        cmm_txbf.o\
        cmm_txbf_cal.o
obj_vht += mgmt_vht.o\
	vht.o


obj-m := mt7610u.o

ccflags-y += -DNEW_RATE_ADAPT_SUPPORT -DCONFIG_STA_SUPPORT -DSYSTEM_LOG_SUPPORT -DCHIPSET=mt7610u -DRESOURCE_PRE_ALLOC -DDOT11_VHT_AC -DENHANCED_STAT_DISPLAY -DSTA_DRIVER_BUILD="\"20141022-1327\"" -DAGGREGATION_SUPPORT -DPIGGYBACK_SUPPORT -DWMM_SUPPORT -DLINUX  -DSTATS_COUNT_SUPPORT -DMT76x0 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DA_BAND_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE -DCONFIG_ANDES_SUPPORT -DMT7650 -DMT7630 -DMT7610 -DDBG -DDOT11_N_SUPPORT
#-DCONFIG_STA_SUPPORT  -DRTMP_USB_SUPPORT -DWPA_SUPPLICANT_SUPPORT -DNATIVE_WPA_SUPPLICANT_SUPPORT -DDOT11_VHT_AC -DMT76x2 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DA_BAND_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE -DCONFIG_ANDES_SUPPORT
#ccflags-y += -DCONFIG_STA_SUPPORT -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DWPA_SUPPLICANT_SUPPORT -DNATIVE_WPA_SUPPLICANT_SUPPORT -DDOT11_VHT_AC -DMT76x2 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DA_BAND_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE -DCONFIG_ANDES_SUPPORT
mt7610u-y := \
	rt_profile.o\
	assoc.o\
	sta_cfg.o\
	sanity.o\
	connect.o\
	auth.o\
	auth_rsp.o\
	sync.o\
	rtmp_data.o\
	wpa.o\
	$(obj_vht)\
	$(obj_cmm)\
	$(obj_wsc)

mt7610-objs += \
	rt_os_util.o\
	sta_ioctl.o\
	rt_linux.o\
	rt_main_dev.o
mt7610-objs += \
	cmm_mat.o \
	cmm_mat_iparp.o \
	cmm_mat_pppoe.o \
	cmm_mat_ipv6.o

mt7610-objs += dls.o
mt7610-objs += \
	wfd.o
mt7610-objs += \
	rt_led.o
mt7610-objs += ate/common/rt_ate.o
mt7610-objs += ate/common/rt_qa.o
mt7610-objs += \
	cfg80211.o \
	cfg80211drv.o
mt7610-objs += \
	cfg80211drv.o
mt7610-objs += \
                cmm_mac_pci.o\
                cmm_data_pci.o\
                rt_rbus_pci_drv.o\
				ee_efuse.o\
                ee_prom.o\
                rt_rf.o\
                rt30xx.o\
				rt65xx.o\
                mt76x0.o\
				ral_nmac.o\
				mcu.o\
                mcu_and.o

mt7610-objs += \
        ee_flash.o
mt7610-objs += \
                rt_pci_rbus.o\
                rt_rbus_pci_util.o\
                pci_main_dev.o

mt7610-objs += \
        frq_cal.o
mt7610-objs += \
                cmm_mac_usb.o\
                cmm_data_usb.o\
				rtusb_io.o\
				rtusb_data.o\
				rtusb_bulk.o\
                rt_usb.o\
                ee_prom.o\
				ee_efuse.o\
                rt_rf.o\
				rt65xx.o\
                mt76x0.o\
                ral_nmac.o\
				mcu.o\
                mcu_and.o

mt7610-objs += \
        		ee_flash.o
mt7610-objs += \
				naf/net_acc.o\
				naf/cso.o
mt7610-objs += \
				naf/net_acc.o\
				naf/cso.o
mt7610-objs += \
	ate/chips/mt76x0_ate.o\
	ate/common/ate_usb.o
mt7610-objs += \
                rt_usb.o\
                rt_usb_util.o\
                usb_main_dev.o\
				rtusb_dev_id.o
mt7610-objs += \
        frq_cal.o


PHONY := clean install uninstall
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f *.o
	rm -f .*.{cmd,flags,d}
	rm -f *.{o,ko,mod.{o,c}}
	rm -f .*.{cmd,flags,d}
	rm -fr .tmp_versions
#Must clean Module.symvers; or you will suffer symbol version not match
#when OS_ABL = YES.
	rm -f Module.symvers
	rm -f Modules.symvers
	rm -f Module.markers
	rm -f modules.order
	rm -f *.o
	rm -f .*.{cmd,flags,d}
ifeq ($(RT28xx_MODE),AP)
	rm -f ap/*.o
	rm -f ap/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),STA)
	rm -f *.o
	rm -f .*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),APSTA)
	rm -f ap/*.o
	rm -f ap/.*.{cmd,flags,d}
	rm -f *.o
	rm -f .*.{cmd,flags,d}
endif
endif
endif

install:
	rm -rf $(DAT_PATH)
	$(shell [ ! -f /etc/Wireless ] && mkdir /etc/Wireless)
	mkdir $(DAT_PATH)
	cp $(RT28xx_DIR)/$(DAT_FILE_NAME) $(DAT_PATH)/.
	install -d $(LINUX_SRC_MODULE)
	install -m 644 -c $(addsuffix .ko,mt7610) $(LINUX_SRC_MODULE)
	/sbin/depmod -a ${shell uname -r}

uninstall:
#	rm -rf $(DAT_PATH)
	rm -rf $(addprefix $(LINUX_SRC_MODULE),$(addsuffix .ko,mt7610))
	/sbin/depmod -a ${shell uname -r}

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
