#include <stdint.h>
#include <memory>
#include <string.h>
#include <functional>
#include "zero_memory.h"

using namespace std;

template <typename T>
unique_ptr<T,function<void(T*)>> make_secure()
{
  return make_secure<T>(sizeof(T));
}

template <typename T>
unique_ptr<T,function<void(T*)>> make_secure(int size)
{
  unique_ptr<T,function<void(T*)>> ptr((T*)malloc(size), [size](T *p)
							 {
							   printf("korekara! %p %d\n", p, size);
							   zero_memory(p, size);
							   printf("free memory!\n");
							   free(p);
							 });
  return std::move(ptr);
}

typedef struct {
  int a;
  int b;
} A;

int main(void)
{
  uint8_t data[10];
  auto ptr = make_secure<uint8_t>(10);
  auto ptr2 = make_secure<A>();

  ptr2->a = 0;
  memset(ptr.get(), 0xFF, 10);
  zero_memory(data, sizeof(data));
  printf("hello\n");
  return 0;
}
