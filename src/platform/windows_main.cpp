#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

void ParseArgs(const char *str, int *pargc, char ***pargv)
{
    CHAR programName[MAX_PATH + 1];
    GetModuleFileName(NULL, programName, MAX_PATH + 1);
    size_t programNameLen = strlen(programName);
    size_t totalSize = programNameLen + 1;

    std::vector<std::string> args;

    std::ostringstream word;
    bool inQuotes = false;
    for (const char *p = str; *p != '\0'; p++) {
        int slashCount = 0;
        while (*p == '\\') {
            slashCount++;
            p++;
        }
        if (*p == '"') {
            word << std::string(slashCount / 2, '\\');
            if (slashCount % 2 == 0) {
                inQuotes = !inQuotes;
            } else {
                word << '"';
            }
        } else {
            word << std::string(slashCount, '\\');
            if (!inQuotes && (*p == ' ' || *p == '\t')) {
                if (!word.str().empty()) {
                    totalSize += word.str().length() + 1;
                    args.push_back(word.str());
                    word = std::ostringstream();
                }
            } else {
                word << *p;
            }
        }
    }

    if (!word.str().empty()) {
        totalSize += word.str().length() + 1;
        args.push_back(word.str());
    }

    *pargc = (int)args.size() + 1;
    *pargv = (char **)malloc(sizeof(char *) * (*pargc) + totalSize);
    char *p = (char *)(*pargv) + sizeof(char *) * (*pargc);

    // Copy program name to argv[0]
    (*pargv)[0] = p;
    const char *s = programName;
    while (*p++ = *s++);

    // Copy command line arguments to argv[1]..argv[argc-1]
    for (size_t i = 0; i < args.size(); i++) {
        (*pargv)[i+1] = p;
        const char *s = args[i].c_str();
        while (*p++ = *s++);
    }
}
