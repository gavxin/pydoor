#include <windows.h>
#include <strsafe.h>
#include <python.h>

#include "pydoor.h"

#define PY_SCRIPT_NAME "door.py"

short volatile inited = 0;
HANDLE thread = INVALID_HANDLE_VALUE;
short volatile door_started = 0;

void foo() {}

void AppendLog(char* msg) {
  OutputDebugStringA(msg);
}


int RunDoor() {
  if (InterlockedCompareExchange16(&door_started, 1, 0) == 1) {
    return 0;
  }

  AppendLog("RunDoor starting...");

  Py_Initialize();

  char path[MAX_PATH] = { 0 };
  ::GetModuleFileNameA(::GetModuleHandleA(NULL), path, MAX_PATH);
  *(::strrchr(path, '\\')) = '\0';
  ::StringCchCatA(path, MAX_PATH, "\\" PY_SCRIPT_NAME);

  FILE* file = NULL;
  if (fopen_s(&file, path, "r") != 0) {
    AppendLog("Could not open " PY_SCRIPT_NAME " file.");
    return 1;
  }

  PyRun_SimpleFile(file, PY_SCRIPT_NAME);

  Py_Finalize();
  fclose(file);

  AppendLog("RunDoor end.");
  return 0;
}

DWORD WINAPI ThreadWork(LPVOID lpParam) {
  return RunDoor();
}

BOOL WINAPI DllMain(
  _In_ HINSTANCE hinstDLL,
  _In_ DWORD     fdwReason,
  _In_ LPVOID    lpvReserved
) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    if (InterlockedCompareExchange16(&inited, 1, 0) == 0) {
      AppendLog("Pydoor DLL Attach!");
      thread = ::CreateThread(NULL, 0, ThreadWork, NULL, 0, NULL);
    }
    break;
  case DLL_PROCESS_DETACH: {
    AppendLog("Pydoor DLL Detach!");
    DWORD ret = ::TerminateThread(thread, 1);
    if (ret == STILL_ACTIVE) {
      return FALSE;
    }
    break;
  }
  default:
    break;
  }
  return TRUE;
}

// vim: sw=2:ts=2