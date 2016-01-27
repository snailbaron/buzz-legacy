#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include "app/application.hpp"

std::vector<std::string> GetArgs(char *str)
{
    std::vector<std::string> args;

    CHAR *p = str;
    std::ostringstream word;
    bool inQuotes = false;
    while (*p != '\0') {
        if (*p == '"') {
            inQuotes = !inQuotes;
            p++;
        } else if (*p == '\\') {
            int slashCount = 0;
            while (*p == '\\') {
                slashCount++;
                p++;
            }
            if (*p == '"') {
                for (int i = 0; i < slashCount / 2; i++) {
                    word << '\\';
                }
                if (slashCount % 2 == 0) {
                    inQuotes = !inQuotes;
                } else {
                    word << '"';
                }
                p++;
            } else {
                for (int i = 0; i < slashCount; i++) {
                    word << '\\';
                }
                word << *p;
                p++;
            }
        } else if (*p == ' ' || *p == '\t') {
            if (inQuotes) {
                word << *p;
            } else {
                if (!word.str().empty()) {
                    args.push_back(word.str());
                    word.clear();
                }
            }
            p++;
        }
    }   
    
    return args;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int)
{
    std::vector<std::string> strings = {
        "\"abc\" d e",
        "a\\\\\\b d\"e f\"g h",
        "a\\\\\\\"b c d",
        "a\\\\\\\\\"b c\" d e"
    };

}

