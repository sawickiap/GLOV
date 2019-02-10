#include "pch.h"
#include "../include/GLOV.h"

int main()
{
    printf("Hello world!\n");

    GLOV::Instance* instance = nullptr;
    GLOV::Result res = GLOV::CreateInstance(instance);
    assert(res == GLOV::Result::Success);

    GLOV::DestroyInstance(instance);
}
