PLATFORM_FLAVOR ?= zc702
PLATFORM_FLAVOR_$(PLATFORM_FLAVOR) := y

# 32-bit flags
arm32-platform-cpuarch		:= cortex-a9
arm32-platform-cflags		+= -mcpu=$(arm32-platform-cpuarch)
arm32-platform-aflags		+= -mcpu=$(arm32-platform-cpuarch)
arm32-platform-aflags		+= -mfpu=neon

$(call force,CFG_CACHE_API,y)
$(call force,CFG_CDNS_UART,y)
$(call force,CFG_SECURE_TIME_SOURCE_REE,y)
$(call force,CFG_GENERIC_BOOT,y)
$(call force,CFG_GIC,y)
$(call force,CFG_PL310,y)
$(call force,CFG_HWSUPP_MEM_PERM_PXN,n)
$(call force,CFG_CRYPTO_WITH_CE,n)
$(call force,CFG_PM_STUBS,y)
$(call force,CFG_ARM32_core,y)

ta-targets = ta_arm32

CFG_TEE_CORE_EMBED_INTERNAL_TESTS ?= y
CFG_TEE_FS_KEY_MANAGER_TEST ?= y
CFG_WITH_STACK_CANARIES ?= y
CFG_WITH_STATS ?= y
