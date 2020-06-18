#ifndef _PERI_GIC_H
#define _PERI_GIC_H
#include <stdint.h>
#include "base.h"
#include "arm/sysregs.h"

typedef volatile struct __attribute__((packed)) {
	uint32_t DCTLR;                 /* 0x0 Distributor Control register */
	const uint32_t DTYPER;          /* 0x4 Controller type register */
	const uint32_t DIIDR;           /* 0x8 Implementer identification register */
	uint32_t _reserved0[13];	    /* 0xC - 0x3C; reserved and implementation-defined */
	uint32_t DSETSPINSR;	    /* 0x40 Non-secure SPI Set Register */
	uint32_t _reserved1;	    /* 0x44 reserved and implementation-defined */
	uint32_t DCLRSPINSR;	    /* 0x48 Non-secure SPI Clear Register */
	uint32_t _reserved2;	    /* 0x4C reserved and implementation-defined */
	uint32_t DSETSPISR;		    /* 0x50 Secure SPI Set Register */
	uint32_t _reserved3;	    /* 0x54 reserved and implementation-defined */
	uint32_t DCLRSPISR;		    /* 0x58 Secure SPI Clear Register */
	uint32_t _reserved4[9];	    /* 0x5C - 0X7C reserved and implementation-defined */
	uint32_t DIGROUPR[32];          /* 0x80 - 0xFC Interrupt group registers */
	uint32_t DISENABLER[32];        /* 0x100 - 0x17C Interrupt set-enable registers */
	uint32_t DICENABLER[32];        /* 0x180 - 0x1FC Interrupt clear-enable registers */
	uint32_t DISPENDR[32];          /* 0x200 - 0x27C Interrupt set-pending registers */
	uint32_t DICPENDR[32];          /* 0x280 - 0x2FC Interrupt clear-pending registers */
	uint32_t DISACTIVER[32];        /* 0x300 - 0x37C Active Bit Registers (GIC v1) */
	uint32_t DICACTIVER[32];        /* 0x380 - 0x3FC Active Bit Registers (GIC v1) */
	uint32_t DIPRIORITY[255];       /* 0x400 - 0x7F8 Interrupt priority registers */
	uint32_t _reserved5;            /* 0x7FC reserved */
	const uint32_t DITARGETSRO[8];  /* 0x800 - 0x81C Interrupt CPU targets, RO */
	uint32_t DITARGETSR[247];       /* 0x820 - 0xBF8 Interrupt CPU targets */
	uint32_t _reserved6;            /* 0xBFC reserved */
	uint32_t DICFGR[64];            /* 0xC00 - 0xCFC Interrupt config registers */
	uint32_t DIGRPMODR[32];            /* 0xD00 - 0xD7C Interrupt Group Modifier Registers */
	uint32_t _reserved7[32];	    /* 0xD80 - 0XDFC reserved and implementation-defined */
	uint32_t DNSACR[64];		/* 0xE00 - 0xEFC Non-secure Access Control Registers */
	uint32_t DSGIR;			/* 0xF00 Software Generated Interrupt Register */
	uint32_t _not_used1[3];		/* 0xF04 - 0xF0C */
	uint32_t DCPENDSGIR[4];		/* 0xF10 - 0xF1C SGI Clear-Pending Registers */
	uint32_t DSPENDSGIR[4];		/* 0xF20 - 0xF2C SGI Set-Pending Registers */
	uint32_t _reserved8[5236];	/* 0xF30 - 0x60FC */
	uint64_t DIROUTER[960];		/* 0x6100 - 0x7EF8 Interrupt Routing Registers, 64-bit */

    /* Some SPI status registers and identification registers beyond this.
       Don't care about them */
} gic_distributor_registers;

#define GIC_BASE		(PBASE + 0x6E00000)
#define GIC_DIST_BASE		(GIC_BASE)

#define INTR_SHIFT		0
#define INTR_BITS		0x1F

#define ARE_BITS		0x1
#define ARE_SHIFT		4

#define GRP1A_SHIFT		1
#define GRP1A_MASK		(0x1 << GRP1A_SHIFT)
#define ENABLE_GRP1A		(1 << GRP1A_SHIFT)

#define GRP1_SHIFT		0
#define GRP1_MASK		(0x1 << GRP1A_SHIFT)
#define ENABLE_GRP1		(1 << GRP1_SHIFT)
#define DISABLE_GRP1		(0 << GRP1_SHIFT)

#define AFF3			32
#define AFF2			16
#define AFF1			8
#define AFF0			0
#define CPU_AFF_MASK		(0xFFUL << AFF3 | 0xF << AFF2 | 0xF << AFF1 | 0xF << AFF0)

#define ICC_SRE_EL1		S3_0_C12_C12_5
#define SRE_MASK		(0x1 << 0)
#define SRE_ENABLE		0x1

#define ICC_CTLR_EL1		S3_0_C12_C12_4
#define CBPR_MASK		(0x1 << 0)
#define EOI_MASK		(0x1 << 1)
#define CBPR_VAL		0
#define EOI_VAL			0

#define ICC_GRPEN1_EL1		S3_0_C12_C12_7
#define ENABLE_MASK		(0x1 << 0)

#define ICC_PMR_EL1		S3_0_C4_C6_0
#define PRIO_MASK		0xFF
#define DEFAULT_PRIO		0xFF

#define MAX_SPI			256
#define SPI_OFFSET		32

#define ICC_IAR1_EL1		S3_0_c12_c12_0
#define ICC_EOIR1_EL1		S3_0_c12_c12_1
#define INTID_MASK		0xffffff
#define INTID_SHIFT		0

#endif /* End of PERI_GIC_H */
