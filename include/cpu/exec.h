#ifndef __CPU_EXEC_H__
#define __CPU_EXEC_H__

#include "nemu.h"
#include "monitor/diff-test.h"
#include "cpu/rtl.h"

#define make_EHelper(name) void concat(exec_, name) (vaddr_t *eip)
typedef void (*EHelper) (vaddr_t *);

#include "cpu/decode.h"

typedef struct {
  DHelper decode;
  EHelper execute;
  int width;
} OpcodeEntry;

#define IDEXW(id, ex, w)   {concat(decode_, id), concat(exec_, ex), w}
#define IDEX(id, ex)       IDEXW(id, ex, 0)
#define EXW(ex, w)         {NULL, concat(exec_, ex), w}
#define EX(ex)             EXW(ex, 0)
#define EMPTY              EX(inv)

static inline uint32_t instr_fetch(vaddr_t *pc, int len) {
  uint32_t instr = vaddr_read(*pc, len);
#ifdef DEBUG
  uint8_t *p_instr = (void *)&instr;
  int i;
  for (i = 0; i < len; i ++) {
    decinfo.p += sprintf(decinfo.p, "%02x ", p_instr[i]);
  }
#endif
  (*pc) += len;
  return instr;
}

/* Instruction Decode and EXecute */
static inline void idex(vaddr_t *pc, OpcodeEntry *e) {
  if (e->decode)
    e->decode(pc);
  e->execute(pc);
}

static inline void update_pc(void) {
  if (decinfo.is_jmp) { decinfo.is_jmp = 0; }
  else { cpu.pc = decinfo.seq_pc; }
}

#ifdef DEBUG
#define print_asm(...) Assert(snprintf(decinfo.assembly, 80, __VA_ARGS__) < 80, "buffer overflow!")
#else
#define print_asm(...)
#endif

#ifndef suffix_char
#define suffix_char(width) ' '
#endif

#define print_asm_template1(instr) \
  print_asm(str(instr) "%c %s", suffix_char(id_dest->width), id_dest->str)

#define print_asm_template2(instr) \
  print_asm(str(instr) "%c %s,%s", suffix_char(id_dest->width), id_src->str, id_dest->str)

#define print_asm_template3(instr) \
  print_asm(str(instr) "%c %s,%s,%s", suffix_char(id_dest->width), id_src->str, id_src2->str, id_dest->str)

#endif
