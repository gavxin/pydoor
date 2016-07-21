#include <windows.h>
#include <stdio.h>

#include "../pydoor/pydoor.h"

int main() {
  printf("Press enter to load library...");
  getchar();
  ::LoadLibraryA("pydoor.dll");
  printf("Sleep...");
  Sleep(60 * 60 * 1000); // 1 hour
  // RunDoor();
  return 0;
}