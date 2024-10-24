#ifndef ADD_H
#define ADD_H

#include <CoreBridge/platform_bridge_interop.h>

#ifdef __cplusplus
extern "C" {
#endif

int addNums(int a, int b);

double getDistance();

void printName();

CStringCore getInfo();

#ifdef __cplusplus
}
#endif

#endif
