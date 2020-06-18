#include "gic.h"
#include "arm/sysregs.h"
#include "bitops.h"

static gic_distributor_registers* gic_dregs;
static uint32_t gic_irq;

static inline void gicd_enable_group1_ns( void )
{
	if (read_reg32_bits(&gic_dregs->DCTLR, ARE_BITS, ARE_SHIFT))
		setclr_reg32_bits(&gic_dregs->DCTLR, GRP1A_MASK, ENABLE_GRP1A);
	else
		setclr_reg32_bits(&gic_dregs->DCTLR, GRP1_MASK, ENABLE_GRP1);
}

static inline void gicd_set_affinity( uint32_t cpu_aff )
{
	unsigned int i, intr;

	for (intr = SPI_OFFSET, i = 0; intr < gic_irq; intr++, i++) {
		setclr_reg64_bits(&gic_dregs->DIROUTER[i],
			       	CPU_AFF_MASK, cpu_aff);
	}
}

static void gicc_enable_sre( void )
{
	uint64_t reg_val;

	reg_val = read_sysreg(ICC_SRE_EL1);
	reg_val &= ~(SRE_MASK);
	reg_val |= SRE_ENABLE;
	write_sysreg(reg_val, ICC_SRE_EL1);
}

static void gicc_config_ctlr( void )
{
	uint64_t reg_val;

	reg_val = read_sysreg(ICC_CTLR_EL1);
	reg_val &= ~(CBPR_MASK|EOI_MASK);
	reg_val |= (CBPR_VAL|EOI_VAL);
	write_sysreg(reg_val, ICC_CTLR_EL1);
}

static void gicc_set_prio_mask( void )
{
	uint64_t reg_val;

	reg_val = read_sysreg(ICC_PMR_EL1);
	reg_val &= ~(PRIO_MASK);
	reg_val |= (DEFAULT_PRIO);
	write_sysreg(reg_val, ICC_PMR_EL1);
}

static void gicc_grp1( unsigned int enable )
{
	uint64_t reg_val;

	reg_val = read_sysreg(ICC_GRPEN1_EL1);
	reg_val &= ~(ENABLE_MASK);
	reg_val |= (enable);
	write_sysreg(reg_val, ICC_GRPEN1_EL1);

}

static void gicc_icc_init( void )
{
	gicc_enable_sre();
	gicc_config_ctlr();
	gicc_set_prio_mask();
	gicc_grp1(ENABLE_GRP1);
}

static void gicd_dist_init( void )
{
	gicd_enable_group1_ns();
	/* we will run on primary CPU only */
	gicd_set_affinity(0);

}

unsigned int get_pending_interrupt( void )
{
	uint32_t reg_val;

	reg_val = read_sysreg(ICC_IAR1_EL1);
	reg_val &= (INTID_MASK << INTID_SHIFT);
	reg_val >>= INTID_SHIFT;
	return reg_val;	
}

static inline void mod_irq_status(unsigned int irq_no, unsigned int enable)
{
	unsigned int irq_group, irq_bit;
	volatile uint32_t* reg;

	irq_group = irq_no / 32;
	irq_bit = irq_no % 32;

	if (enable)
		reg = &gic_dregs->DISENABLER[irq_group];
	else
		reg = &gic_dregs->DICENABLER[irq_group];

	setclr_reg32_bits(reg,	1 << irq_bit, 1 << irq_bit);
}

static inline void set_irq_type(unsigned int irq_no, irq_type_t type)
{
	unsigned int irq_group, type_bit;

	irq_group = irq_no / 16;
	type_bit = 2 * (irq_no % 16) + 1; // type is 2x + 1
	setclr_reg32_bits(&gic_dregs->DICFGR[irq_group], 1 << type_bit,
			type << type_bit);
}

void enable_irq(unsigned int irq_no, irq_type_t type)
{
	mod_irq_status(irq_no, ENABLE_IRQ);
	set_irq_type(irq_no, type);
}

void disable_irq(unsigned int irq_no)
{
	mod_irq_status(irq_no, DISABLE_IRQ);
}

void deactivate_interrupt( unsigned int irq )
{
	write_sysreg(irq, ICC_EOIR1_EL1);
}

void generate_irq( unsigned int irq_no )
{
	unsigned int irq_group, irq_bit;

	irq_group = irq_no / 32;
	irq_bit = irq_no % 32;
	setclr_reg32_bits(&gic_dregs->DISPENDR[irq_group],
		       	1 << irq_bit, 1 << irq_bit);
}

void gic_init( void )
{
	gic_dregs = (gic_distributor_registers*) GIC_DIST_BASE;
	gic_irq = 32 * ( read_reg32_bits(&gic_dregs->DTYPER, INTR_BITS,
			       	INTR_SHIFT) + 1 ) - 1;

	gicd_dist_init();

	/* 
	 * GIC redistributor has been configured to wakeup
	 * all connected PE in tpl 
	 */

	/* cpu interfaces setup */
	gicc_icc_init();
}
