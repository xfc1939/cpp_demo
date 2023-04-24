#ifndef __ALIGN_TEST_H_
#define __ALIGN_TEST_H_
#include <memory>
#include "Log.h"

void Align_Test()
{
    void *ptr = malloc(10);
    size_t size = 10;
    std::byte *ptr_byte = static_cast<std::byte*>(ptr);
    ++ptr_byte;
    void *ptr_void = static_cast<void*>(ptr_byte);
    LOG_DEBUG() << ptr << ptr_byte << (ptr_byte+1) << size;
    std::align(3, 3, ptr_void, size);
    LOG_DEBUG() << ptr_void << size;
}

#endif