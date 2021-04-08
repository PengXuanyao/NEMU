def_DEWBWHelper(xorl_G2E , G2E, xor, E, l);
def_DEWBWHelper(xorw_G2E , G2E, xor, E, w);
def_DEWBWHelper(xorb_G2E , G2E, xor, E, b);
def_DEWBWHelper(xorl_E2G , E2G, xor, r, l);
def_DEWBWHelper(xorw_E2G , E2G, xor, r, w);
def_DEWBWHelper(xorb_E2G , E2G, xor, r, b);
def_DEWBWHelper(xorl_SI2E,   E, xor, E, l);
def_DEWBWHelper(xorw_SI2E,   E, xor, E, w);
def_DEWBWHelper(xorl_I2a ,   r, xor, r, l);
def_DEWBWHelper(xorw_I2a ,   r, xor, r, w);

def_DEWBWHelper(orl_G2E, G2E, or, E, l);
def_DEWBWHelper(orw_G2E, G2E, or, E, w);
def_DEWBWHelper(orl_E2G, E2G, or, r, l);
def_DEWBWHelper(orw_E2G, E2G, or, r, w);
def_DEWBWHelper(orb_E2G, E2G, or, r, b);
def_DEWBWHelper(orl_I2E ,  E, or, E, l);
def_DEWBWHelper(orw_I2E ,  E, or, E, w);
def_DEWBWHelper(orb_I2E ,  E, or, E, b);
def_DEWBWHelper(orl_SI2E,  E, or, E, l);
def_DEWBWHelper(orw_SI2E,  E, or, E, w);
def_DEWBWHelper(orl_I2a,   r, or, r, l);
def_DEWBWHelper(orw_I2a,   r, or, r, w);

def_DEWBWHelper(andl_G2E ,  G2E, and, E, l);
def_DEWBWHelper(andw_G2E ,  G2E, and, E, w);
def_DEWBWHelper(andl_E2G ,  E2G, and, r, l);
def_DEWBWHelper(andw_E2G ,  E2G, and, r, w);
def_DEWBWHelper(andb_E2G ,  E2G, and, r, b);
def_DEWBWHelper(andl_I2a ,    r, and, r, l);
def_DEWBWHelper(andw_I2a ,    r, and, r, w);
def_DEWBWHelper(andl_I2E ,    E, and, E, l);
def_DEWBWHelper(andw_I2E ,    E, and, E, w);
def_DEWBWHelper(andl_SI2E,    E, and, E, l);
def_DEWBWHelper(andw_SI2E,    E, and, E, w);

def_DEWBWHelper(shll_Ib2E,    E, shl, E, l);
def_DEWBWHelper(shlw_Ib2E,    E, shl, E, w);
def_DEWBWHelper(shll_cl2E,    E, shl, E, l);
def_DEWBWHelper(shlw_cl2E,    E, shl, E, w);

def_DEWBWHelper(shrl_Ib2E,    E, shr, E, l);
def_DEWBWHelper(shrw_Ib2E,    E, shr, E, w);
def_DEWBWHelper(shrl_cl2E,    E, shr, E, l);
def_DEWBWHelper(shrw_cl2E,    E, shr, E, w);
def_DEWBWHelper(shrl_1_E ,    E, shr, E, l);
def_DEWBWHelper(shrw_1_E ,    E, shr, E, w);
def_DEWBWHelper(shrb_1_E ,    E, shr, E, b);

def_DEWBWHelper(sarl_Ib2E,    E, sar, E, l);
def_DEWBWHelper(sarw_Ib2E,    E, sar, E, w);
def_DEWBWHelper(sarl_cl2E,    E, sar, E, l);
def_DEWBWHelper(sarw_cl2E,    E, sar, E, w);
def_DEWBWHelper(sarl_1_E ,    E, sar, E, l);
def_DEWBWHelper(sarw_1_E ,    E, sar, E, w);

def_DEWHelper(testl_G2E,  G2E, test, l);
def_DEWHelper(testw_G2E,  G2E, test, w);
def_DEWHelper(testb_G2E,  G2E, test, b);
def_DEWHelper(testl_I2E,    E, test, l);
def_DEWHelper(testw_I2E,    E, test, w);
def_DEWHelper(testb_I2E,    E, test, b);
def_DEWHelper(testb_I2a,    r, test, b);

def_EWBWHelper(setcc, setcc, E, b);

def_EWBWHelper(notl_E, not, E, l);
def_EWBWHelper(notw_E, not, E, w);

def_DEWBWHelper(roll_cl2E,    E, rol, E, l);
def_DEWBWHelper(rolw_cl2E,    E, rol, E, w);

#if 0
static inline def_EHelper(ror) {
  rtl_shr(s, s0, ddest, dsrc1);
  rtl_li(s, s1, id_dest->width * 8);
  rtl_sub(s, s1, s1, dsrc1);
  rtl_shl(s, s1, ddest, s1);
  rtl_or(s, ddest, s0, s1);

  operand_write(s, id_dest, ddest);
  // unnecessary to update eflags in NEMU
  //difftest_skip_eflags(EFLAGS_MASK_ALL);
  print_asm_template2(ror);
}

static inline def_EHelper(shld) {
  assert(id_dest->width == 4);
  rtl_shl(s, s0, ddest, dsrc1);

  rtl_li(s, s1, 31);
  rtl_sub(s, s1, s1, dsrc1);
  // shift twice to deal with dsrc1 = 0
  // the first shift is still right even if we do not
  // mask out the high part of `dsrc1`, since we have
  //   (31 - (dsrc1 & 0x1f)) = (31 - dsrc1 % 32) = (31 - dsrc1) mod 32
  rtl_shr(s, s1, dsrc2, s1);
  rtl_shri(s, s1, s1, 1);

  rtl_or(s, ddest, s0, s1);

  operand_write(s, id_dest, ddest);
#ifndef CONFIG_LAZY_CC
  rtl_update_ZFSF(s, ddest, id_dest->width);
  // unnecessary to update CF and OF in NEMU
#endif
  print_asm_template3(shld);
}

static inline def_EHelper(shrd) {
  assert(id_dest->width == 4);

#ifdef CONFIG_ENGINE_INTERPRETER
  int count = *dsrc1 & 0x1f;
  if (count == 0) {
    operand_write(s, id_dest, ddest);
    print_asm_template3(shrd);
    return;
  }
#endif
  rtl_subi(s, s0, dsrc1, 1);
  rtl_shr(s, s1, ddest, s0); // shift (cnt - 1)
  rtl_andi(s, s0, s1, 0x1);
  rtl_set_CF(s, s0);
  rtl_shr(s, s0, ddest, dsrc1);

  rtl_li(s, s1, 31);
  rtl_sub(s, s1, s1, dsrc1);
  // shift twice to deal with dsrc1 = 0
  // the first shift is still right even if we do not
  // mask out the high part of `dsrc1`, since we have
  //   (31 - (dsrc1 & 0x1f)) = (31 - dsrc1 % 32) = (31 - dsrc1) mod 32
  rtl_shl(s, s1, dsrc2, s1);
  rtl_shli(s, s1, s1, 1);

  rtl_or(s, ddest, s0, s1);

  operand_write(s, id_dest, ddest);
#ifndef CONFIG_LAZY_CC
  rtl_update_ZFSF(s, ddest, id_dest->width);
  // unnecessary to update CF and OF in NEMU
#endif
  print_asm_template3(shrd);
}

static inline def_EHelper(rcr) {
  rtl_shr(s, s0, ddest, dsrc1);

  rtl_get_CF(s, s1);
  rtl_shli(s, s1, s1, 31);
  rtl_shr(s, s1, s1, dsrc1);
  rtl_shli(s, s1, s1, 1);
  rtl_or(s, s0, s0, s1);

  rtl_li(s, s1, 1);
  rtl_shl(s, s1, s1, dsrc1);
  rtl_shri(s, s1, s1, 1);
  rtl_and(s, s1, ddest, s1);
  rtl_setrelopi(s, RELOP_NE, s1, s1, 0);
  rtl_set_CF(s, s1);

  rtl_li(s, s1, id_dest->width * 8);
  rtl_sub(s, s1, s1, dsrc1);
  rtl_shl(s, s1, ddest, s1);
  rtl_shli(s, s1, s1, 1);
  rtl_or(s, ddest, s0, s1);

  operand_write(s, id_dest, ddest);
  print_asm_template2(rcr);
}

static inline def_EHelper(rcl) {
  rtl_shl(s, s0, ddest, dsrc1);

  rtl_get_CF(s, s1);
  rtl_shl(s, s1, s1, dsrc1);
  rtl_shri(s, s1, s1, 1);
  rtl_or(s, s0, s0, s1);

  rtl_li(s, s1, 0x80000000);
  rtl_shr(s, s1, s1, dsrc1);
  rtl_shli(s, s1, s1, 1);
  rtl_and(s, s1, ddest, s1);
  rtl_setrelopi(s, RELOP_NE, s1, s1, 0);
  rtl_set_CF(s, s1);

  rtl_li(s, s1, id_dest->width * 8);
  rtl_sub(s, s1, s1, dsrc1);
  rtl_shr(s, s1, ddest, s1);
  rtl_shri(s, s1, s1, 1);
  rtl_or(s, ddest, s0, s1);

  operand_write(s, id_dest, ddest);
  print_asm_template2(rcl);
}
#endif
