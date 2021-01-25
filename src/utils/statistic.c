#include <common.h>
#include <time.h>
#include <locale.h>

static_assert(CLOCKS_PER_SEC == 1000000, "CLOCKS_PER_SEC != 1000000");
static_assert(sizeof(clock_t) == 8, "sizeof(clock_t) != 8");

uint64_t g_timer = 0; // unit: us
uint64_t g_nr_guest_instr = 0;

uint64_t get_time() {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC_COARSE, &now);
  uint64_t us = now.tv_sec * 1000000 + now.tv_nsec / 1000;
  return us;
}

void monitor_statistic() {
  setlocale(LC_NUMERIC, "");
  Log("total guest instructions = %'ld", g_nr_guest_instr);
  Log("host time spent = %'ld us", g_timer);
  if (g_timer > 0) Log("simulation frequency = %'ld instr/s", g_nr_guest_instr * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}
