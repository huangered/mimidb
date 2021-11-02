#include "storage/bufmgr.hpp"

typedef struct BufferStrategyControl {
  int firstFreeBuffer;
  int lastFreeBuffer;
} BufferStrategyControl;

static BufferStrategyControl* StrategyControl = nullptr;

void
StrategyInit(){
  StrategyControl = (BufferStrategyControl*)std::malloc(sizeof(BufferStrategyControl));
  StrategyControl->firstFreeBuffer = 0;
  StrategyControl->lastFreeBuffer = NBuffers - 1;
}

Buffer
FindFreeBuffer() {

  printf("not find free buffer\n");
  
  return 0;
}
