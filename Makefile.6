include $(RT28xx_DIR)/os/linux/config.mk

obj_wsc :=
obj_vht :=
obj_cmm := \
	../../crypt_md5.o\
        ../../crypt_sha2.o\
        ../../crypt_hmac.o\
        ../../crypt_aes.o\
        ../../crypt_arc4.o\
        ../../mlme.o\
        ../../cmm_wep.o\
        ../../action.o\
        ../../cmm_data.o\
	../../rtmp_init.o\
        ../../rtmp_init_inf.o\
        ../../cmm_tkip.o\
        ../../cmm_aes.o\
        ../../cmm_sync.o\
        ../../eeprom.o\
        ../../cmm_sanity.o\
        ../../cmm_info.o\
        ../../cmm_cfg.o\
        ../../cmm_wpa.o\
        ../../cmm_radar.o\
	../../spectrum.o\
        ../../rtmp_timer.o\
        ../../rt_channel.o\
        ../../cmm_profile.o\
        ../../cmm_asic.o\
        ../../scan.o\
        ../../cmm_cmd.o\
        ../../uapsd.o\
	../../ps.o\
	../../rate_ctrl/ra_ctrl.o\
        ../../rate_ctrl/alg_legacy.o\
        ../../rate_ctrl/alg_ags.o\
	../../rtmp_chip.o\
		../../txpower.o\
	../../rtmp_mac.o\
	../../mgmt_hw.o\
	../../mgmt_entrytb.o\
        ../../rtmp_phy.o\
        ../../rlt_phy.o\
	../../rlt_rf.o

ifeq ($(HAS_BLOCK_NET_IF),y)
obj_cmm += ../../netif_block.o
endif

ifeq ($(HAS_NEW_RATE_ADAPT_SUPPORT),y)
obj_cmm += ../../rate_ctrl/alg_grp.o
endif

ifeq ($(HAS_RATE_ADAPT_AGS_SUPPORT),y)
obj_cmm += ../../rate_ctrl/alg_ags.o
endif

ifeq ($(HAS_DFS_SUPPORT),y)
obj_cmm += ../../cmm_dfs.o
endif

ifeq ($(HAS_CS_SUPPORT),y)
obj_cmm += ../../cmm_cs.o
endif

#ifdef DOT11_N_SUPPORT
ifeq ($(HAS_DOT11_N_SUPPORT),y)
obj_cmm += \
        ../../ba_action.o\
        ../../mgmt_ht.o

#ifdef TXBF_SUPPORT
ifeq ($(HAS_TXBF_SUPPORT),y)
obj_cmm += \
        ../../cmm_txbf.o\
        ../../cmm_txbf_cal.o
endif
#endif // TXBF_SUPPORT //
endif
#endif // DOT11_N_SUPPORT //

#ifdef DOT11_VHT_SUPPORT
ifeq ($(HAS_DOT11_VHT_SUPPORT),y)
obj_vht += ../../mgmt_vht.o\
	../../vht.o
endif
#endif // DOT11_VHT_SUPPORT //




#ifdef CONFIG_STA_SUPPORT
ifeq ($(RT28xx_MODE), STA)
MOD_NAME = $(MODULE)_sta
ifeq ($(PLATFORM),MT85XX)
MOD_NAME = rtsta
endif
ifeq ($(PLATFORM),MT53XX)
MOD_NAME = rtsta
endif
DAT_PATH = /etc/Wireless/RT$(CHIPSET_DAT)STA
DAT_FILE_NAME = conf/RT$(CHIPSET_DAT)STA.dat
endif
#endif // CONFIG_STA_SUPPORT //


obj-m := $(MOD_NAME).o


#ifdef CONFIG_STA_SUPPORT
ifeq ($(RT28xx_MODE), STA)
$(MOD_NAME)-objs := \
	../../rt_profile.o\
	../../assoc.o\
	../../sta_cfg.o\
	../../sanity.o\
	../../connect.o\
	../../auth.o\
	../../auth_rsp.o\
	../../sync.o\
	../../rtmp_data.o\
	../../wpa.o\
	$(obj_vht)\
	$(obj_cmm)\
	$(obj_wsc)


ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
	../../rt_os_util.o\
	../../sta_ioctl.o\
	../../rt_linux.o\
	../../rt_main_dev.o
else
$(MOD_NAME)-objs += \
	../../rt_symb.o
endif

#ifdef ETH_CONVERT
ifeq ($(HAS_ETH_CONVERT_SUPPORT), y)
$(MOD_NAME)-objs += \
	../../cmm_mat.o \
	../../cmm_mat_iparp.o \
	../../cmm_mat_pppoe.o \
	../../cmm_mat_ipv6.o
endif
#endif // ETH_CONVERT //




ifeq ($(HAS_QOS_DLS_SUPPORT),y)
$(MOD_NAME)-objs += ../../dls.o
endif


#ifdef WFD_SUPPORT
ifeq ($(HAS_WFD_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../wfd.o
endif
#endif // WFD_SUPPORT //


#ifdef LED_CONTROL_SUPPORT
ifeq ($(HAS_LED_CONTROL_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../rt_led.o
endif
#endif // LED_CONTROL_SUPPORT //


ifeq ($(HAS_ATE),y)
$(MOD_NAME)-objs += ../../ate/common/rt_ate.o
endif

ifeq ($(HAS_QA_SUPPORT),y)
$(MOD_NAME)-objs += ../../ate/common/rt_qa.o
endif







#ifdef CRDA_SUPPORT
ifeq ($(OSABL),NO)
ifeq ($(HAS_CFG80211_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../cfg80211.o \
	../../cfg80211drv.o
endif
endif

ifeq ($(OSABL),YES)
ifeq ($(HAS_CFG80211_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../cfg80211drv.o
endif
endif
#endif // CRDA_SUPPORT //


endif
#endif // CONFIG_STA_SUPPORT //



#chip releated





















#ifdef RT3290
ifneq ($(findstring rt3290,$(CHIPSET)),)
$(MOD_NAME)-objs += \
	../../cmm_mac_pci.o\
	../../cmm_data_pci.o\
	../../rt_rbus_pci_drv.o\
	../../mcu.o\
	../../mcu_51.o\
	../../ee_prom.o\
	../../ee_efuse.o\
	../../rt_rf.o\
	../../rt30xx.o\
	../../rt3290.o

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
        ../../rt_pci_rbus.o\
        ../../rt_rbus_pci_util.o\
        ../../pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
	../../frq_cal.o
endif

endif
#endif // RT3290 //

#ifdef RT6592
ifneq ($(findstring rt6592,$(CHIPSET)),)
$(MOD_NAME)-objs += \
        ../../cmm_mac_pci.o\
        ../../cmm_data_pci.o\
        ../../rt_rbus_pci_drv.o\
        ../../mcu.o\
		../../rtmp_M51.o\
        ../../ee_prom.o\
        ../../ee_efuse.o\
        ../../rt_rf.o\
        ../../rt6592.o

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
        ../../rt_pci_rbus.o\
        ../../rt_rbus_pci_util.o\
        ../../pci_main_dev.o
endif
endif
#endif // RT6592 //





#ifdef MT76x0
ifneq ($(or $(findstring mt7650e,$(CHIPSET)),$(findstring mt7630e,$(CHIPSET)),$(findstring mt7610e,$(CHIPSET))),)
$(MOD_NAME)-objs += \
                ../../cmm_mac_pci.o\
                ../../cmm_data_pci.o\
                ../../rt_rbus_pci_drv.o\
				../../ee_efuse.o\
                ../../ee_prom.o\
                ../../rt_rf.o\
                ../../rt30xx.o\
				../../rt65xx.o\
                ../../mt76x0.o\
				../../ral_nmac.o\
				../../mcu.o\
                ../../mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        ../../ee_flash.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../rt_pci_rbus.o\
                ../../rt_rbus_pci_util.o\
                ../../pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        ../../frq_cal.o
endif

endif
#endif // MT76x0 //

#ifdef MT76x0
ifneq ($(or $(findstring mt7650u,$(CHIPSET)),$(findstring mt7630u,$(CHIPSET)),$(findstring mt7610u,$(CHIPSET))),)
$(MOD_NAME)-objs += \
                ../../cmm_mac_usb.o\
                ../../cmm_data_usb.o\
				../../rtusb_io.o\
				../../rtusb_data.o\
				../../rtusb_bulk.o\
                ../../rt_usb.o\
                ../../ee_prom.o\
				../../ee_efuse.o\
                ../../rt_rf.o\
				../../rt65xx.o\
                ../../mt76x0.o\
                ../../ral_nmac.o\
				../../mcu.o\
                ../../mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        		../../ee_flash.o
endif

ifeq ($(HAS_TSO_SUPPORT),y)
$(MOD_NAME)-objs += \
				../../naf/net_acc.o\
				../../naf/cso.o
endif

ifeq ($(HAS_CSO_SUPPORT), y)
$(MOD_NAME)-objs += \
				../../naf/net_acc.o\
				../../naf/cso.o
endif

ifeq ($(HAS_ATE),y)
$(MOD_NAME)-objs += \
	../../ate/chips/mt76x0_ate.o\
	../../ate/common/ate_usb.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../rt_usb.o\
                ../../rt_usb_util.o\
                ../../usb_main_dev.o\
				../../rtusb_dev_id.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        ../../frq_cal.o
endif

endif
#endif // MT76x0 //


#ifdef RT8592
ifneq ($(findstring rt8592,$(CHIPSET)),)
$(MOD_NAME)-objs += \
                ../../cmm_mac_pci.o\
                ../../cmm_data_pci.o\
                ../../rt_rbus_pci_drv.o\
                ../../ee_prom.o\
				../../ee_efuse.o\
                ../../rt_rf.o\
                ../../rt30xx.o\
				../../rt65xx.o\
				../../rt6592.o\
                ../../rt85592.o\
                ../../ral_nmac.o\
				../../mcu.o\
                ../../mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        		../../ee_flash.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../rt_pci_rbus.o\
                ../../rt_rbus_pci_util.o\
                ../../pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        		../../frq_cal.o
endif

endif
#endif // RT8592 //


PHONY := clean install uninstall

clean:
	rm -f ../../*.o
	rm -f ../../.*.{cmd,flags,d}
	rm -f ../../*.{o,ko,mod.{o,c}}
	rm -f ../../.*.{cmd,flags,d}
	rm -fr ../../.tmp_versions
#Must clean Module.symvers; or you will suffer symbol version not match
#when OS_ABL = YES.
	rm -f ../../Module.symvers
	rm -f ../../Modules.symvers
	rm -f ../../Module.markers
	rm -f ../../modules.order
	rm -f ../../*.o
	rm -f ../../.*.{cmd,flags,d}
ifeq ($(RT28xx_MODE),AP)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),STA)
	rm -f ../../*.o
	rm -f ../../.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),APSTA)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
	rm -f ../../*.o
	rm -f ../../.*.{cmd,flags,d}
endif
endif
endif

install:
	rm -rf $(DAT_PATH)
	$(shell [ ! -f /etc/Wireless ] && mkdir /etc/Wireless)
	mkdir $(DAT_PATH)
	cp $(RT28xx_DIR)/$(DAT_FILE_NAME) $(DAT_PATH)/.
	install -d $(LINUX_SRC_MODULE)
	install -m 644 -c $(addsuffix .ko,$(MOD_NAME)) $(LINUX_SRC_MODULE)
	/sbin/depmod -a ${shell uname -r}

uninstall:
#	rm -rf $(DAT_PATH)
	rm -rf $(addprefix $(LINUX_SRC_MODULE),$(addsuffix .ko,$(MOD_NAME)))
	/sbin/depmod -a ${shell uname -r}

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
