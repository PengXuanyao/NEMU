#include <isa.h>
#include <utils.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

CPU_state cpu = {};
static bool g_print_step = false;
const rtlreg_t rzero = 0;

#ifdef DEBUG
void debug_hook(vaddr_t this_pc, int len) {
  void asm_print(vaddr_t this_pc, int instr_len, bool print_flag);
  asm_print(this_pc, len, g_print_step);

  void scan_watchpoint(vaddr_t this_pc);
  scan_watchpoint(this_pc);

}
#endif

void execute(uint64_t n);

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INSTR_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  while (nemu_state.state == NEMU_RUNNING) {
    execute(n);
#ifdef HAS_IOE
    extern void device_update();
    device_update();
#endif

#if !defined(DIFF_TEST) && !_SHARE
    void query_intr();
    query_intr();
#endif
  }

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
      Log("nemu: %s\33[0m at pc = " FMT_WORD "\n\n",
          (nemu_state.state == NEMU_ABORT ? "\33[1;31mABORT" :
           (nemu_state.halt_ret == 0 ? "\33[1;32mHIT GOOD TRAP" : "\33[1;31mHIT BAD TRAP")),
          nemu_state.halt_pc);
      // fall through
    case NEMU_QUIT:
      monitor_statistic();
  }
}
