#include "string/iString.h"
#include <chrono>
#include <iostream>
using istring = MiracleForest::String::iString;

#define TESTSTR                                                                                                                             \
    "Hello world!你好世界！Привет, мир!Witaj świecie!안녕하세요!こんにちは！Hej världen!¡Hola, mundo!Γεια " \
    "σας "                                                                                                                               \
    "κόσμε!Chào thế giới!สวัสดีชาวโลก!හෙලෝ "                                                      \
    "වර්ල්ඩ්!ສະ​ບາຍ​ດີ​ຊາວ​ໂລກ!नमस्कार विश्व !مرحبا "          \
    "بالعالم!ހެލޯ "                                                                                                              \
    "ވޯލްޑް!"
#define TESTSTRU8                                                                                                                    \
    u8"Hello world!你好世界！Привет, мир!Witaj świecie!안녕하세요!こんにちは！Hej världen!¡Hola, "       \
    u8"mundo!Γεια σας "                                                                                                       \
    u8"κόσμε!Chào thế giới!สวัสดีชาวโลก!හෙලෝ "                                             \
    u8"වර්ල්ඩ්!ສະ​ບາຍ​ດີ​ຊາວ​ໂລກ!नमस्कार विश्व !مرحبا " \
    u8"بالعالم!ހެލޯ "                                                                                                     \
    u8"ވޯލްޑް!"


void compare()
{
    char  c[] = TESTSTR;
    char* d   = c + 5;
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < 1000'0000; i++) { std::string str(d); }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "\033[38;2;160;255;112m"
                     "std::string took "
                  << duration.count() << " ms to execute." << std::endl;
    }
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < 1000'0000; i++) { istring str(d); }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "\033[38;2;140;230;255m"
                     "istring     took "
                  << duration.count() << " ms to execute." << std::endl;
    }
}

int main()
{
    system("chcp 65001");
    char8_t c[] = TESTSTRU8;
    istring str = TESTSTR;
    // istring  str1(c);
    std::cout << (const char*)c << std::endl;
    std::cout << str << std::endl;
    std::cout << "\033[38;2;240;255;100m"
                 "hash: "
              << std::hash<istring>()(str) << std::endl;
    std::cout << "\033[38;2;255;112;245m"
                 "Press any key to start the test."
              << std::endl;
    std::cin.get();
    std::cin.get();
    for (size_t i = 0; i < 10; i++) { compare(); }
    return 0;
}