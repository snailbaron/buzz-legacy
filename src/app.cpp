#include <cstdio>
#include <direct.h>
#include <cmath>
#include <intrin.h>
#include "app.hpp"
#include "error.hpp"

#define APP_SUFX "Buzz"
#define MEGABYTE (1024 * 1024)

char const * const LangDllName = "Lang" APP_SUFX ".dll";

// Check if there are other instances of the program running.
bool IsOnlyInstance(const char *title)
{
    // Only one instance at a time may perform this check. Create a mutex to ensure this.
    HANDLE mutex = CreateMutex(NULL, TRUE, title);
    if (GetLastError() != ERROR_SUCCESS) {
        // Try to find another window by window class
        HWND wnd = FindWindow(title, NULL);
        if (wnd) {
            // Another instance is running
            ShowWindow(wnd, SW_SHOWNORMAL);
            SetFocus(wnd);
            SetForegroundWindow(wnd);
            SetActiveWindow(wnd);
            return false;
        }
    }
    return true;
}

// Check that there is enough space on hard disk
void CheckHardDisk(const unsigned long long spaceRequired)
{
    const int drive = _getdrive();
    struct _diskfree_t diskfree;
    _getdiskfree(drive, &diskfree);
    const unsigned long long neededClusters = spaceRequired / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);
    if (diskfree.avail_clusters < neededClusters) {
        // Not enough disk space
        throw Error(ERR_INIT_NOT_ENOUGH_DISK_SPACE);
    }
}

// Check that there is enough physical and virtual memory
void CheckMemory(const unsigned long long physMemRequired, const unsigned long long virtMemRequired)
{
    MEMORYSTATUSEX status;
    GlobalMemoryStatusEx(&status);
    if (status.ullTotalPhys < physMemRequired) {
        throw Error(ERR_INIT_NOT_ENOUGH_PHYS_MEMORY);
    }

    if (status.ullAvailVirtual < virtMemRequired) {
        throw Error(ERR_INIT_NOT_ENOUGH_VIRT_MEMORY);
    }

    // TODO: GCC_NEW?
    char *buf = new char[virtMemRequired];
    if (buf) {
        delete[] buf;
    } else {
        throw Error(ERR_INIT_NOT_ENOUGH_CONTIG_MEMORY);
    }
}



bool App::InitInstance(HINSTANCE hInstance, LPSTR cmdLine)
{
    // TODO: Check multiple instances?

    // Disable mouse cursor by default. The game should turn it on.
    SetCursor(NULL);

    // Load string table from language resource DLL
    /*
    char appPath[MAX_PATH + 1] = {0};
    GetModuleFileName(NULL, appPath, MAX_PATH);
    char *pSep = strrchr(appPath, '\\');
    if (pSep == NULL) {
        strcpy(appPath, LangDllName);
    } else {
        strcpy(pSep + 1, LangDllName);
    }
    m_langDll = LoadLibrary(appPath);
    if (!m_langDll) {
        char msg[4096];
        sprintf(msg, "Error: %s not found\n", LangDllName);
        MessageBox(NULL, msg, "Error", MB_OK | MB_ICONERROR);
        return false;
    }
    */

    // Check machine resources
    bool resourceCheck = false;
    while (!resourceCheck) {
        try {
            const DWORD physRam = 512 * MEGABYTE;
            const DWORD virtRam = 1024 * MEGABYTE;
            CheckMemory(physRam, virtRam);

            const int diskSpace = 10 * MEGABYTE;
            CheckHardDisk(diskSpace);

            // TODO: Check CPU speed? If possible at all.

        } catch (Error err) {
            err.ErrCode(); // TODO: Report error during resource checking
            return false;
        }
        
        resourceCheck = true;
    }

    // Set application instance, and parse command line options
    m_hInstance = hInstance;
    // TODO: m_gameOptions = new GameOptions("m_Options->ini");
    // TODO: ParseCommandLine(cmdLine);

    // Initialize resource cache
    // TODO: m_resCache = new ResCache(...)

    // TODO: Initialize Lua state manager, and run initial script

    // Create event manager
    // TODO: m_eventManager = new EventManager(...); if (!m_eventManager) { return false; }

    // Run initialization file
    // TODO: const bool luaInitSuccess = m_luaStateManager->Init("data\\scripts\\init.lua");
    // if (!luaInitSuccess) { return false; }

    // TODO: Check game options, attach to game server or create one

    // Initialize gfx framework, create window, device, etc. Fonts.

    m_isRunning = true;

    return true;
}

