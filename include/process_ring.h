#include <xinu.h>


process process_ring(int32, volatile int32*, volatile int32[]);
extern  int32 r;
extern  int32 p;
extern volatile int32 rounds;
process process_ring_message(int32, volatile pid32[], pid32);

