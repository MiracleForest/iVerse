#include "string/iString.h"
#include <chrono>
#include <iostream>
#include <utility>
using istring = MiracleForest::String::iString;

#define TESTSTR                                                                                                                             \
    "Hello world!你好世界！Привет, мир!Witaj świecie!안녕하세요!こんにちは！Hej världen!¡Hola, mundo!Γεια " \
    "σας "                                                                                                                               \
    "κόσμε!Chào thế giới!สวัสดีชาวโลก!හෙලෝ "                                                      \
    "වර්ල්ඩ්!ສະ​ບາຍ​ດີ​ຊາວ​ໂລກ!नमस्कार "                                      \
    "विश्व "                                                                                                                      \
    "!مرحبا "                                                                                                                          \
    "بالعالم!ހެލޯ "                                                                                                              \
    "ވޯލްޑް!"
#define TESTSTRU8                                                                                                              \
    u8"Hello world!你好世界！Привет, мир!Witaj świecie!안녕하세요!こんにちは！Hej världen!¡Hola, " \
    u8"mundo!Γεια σας "                                                                                                 \
    u8"κόσμε!Chào thế giới!สวัสดีชาวโลก!හෙලෝ "                                       \
    u8"වර්ල්ඩ්!ສະ​ບາຍ​ດີ​ຊາວ​ໂລກ!नमस्कार "                       \
    u8"विश्व "                                                                                                       \
    u8"!مرحبا "                                                                                                           \
    u8"بالعالم!ހެލޯ "                                                                                               \
    u8"ވޯލްޑް!"


std::pair<size_t, size_t> compare()
{
    char   c[]           = TESTSTR;
    char*  d             = c + 5;
    size_t stdStringTook = 0;
    size_t istringTook   = 0;
    using Clock          = std::chrono::high_resolution_clock;

    {
        auto start = Clock::now();
        for (size_t i = 0; i < 1000'0000; i++) { std::string str(d); }
        auto end      = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        stdStringTook = duration.count();
        std::cout << "\033[38;2;160;255;112m";
        std::cout << "std::string took " << stdStringTook << " ms to execute." << std::endl;
    }
    {
        auto start = Clock::now();
        for (size_t i = 0; i < 1000'0000; i++) { istring str(d); }
        auto end      = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        istringTook   = duration.count();
        std::cout << "\033[38;2;140;230;255m";
        std::cout << "istring     took " << istringTook << " ms to execute." << std::endl;
    }
    return std::make_pair(stdStringTook, istringTook);
}

int main()
{
    system("chcp 65001");
    char8_t c[] = TESTSTRU8;
    istring str = TESTSTRU8;
    // istring  str1(c);
    std::cout << (const char*)c << std::endl;
    std::cout << str << std::endl;
    std::cout << "\033[38;2;240;255;100m";
    std::cout << "hash: " << std::hash<istring>()(str) << std::endl;
    std::cout << "\033[38;2;255;112;245m" << std::endl;
    std::cout << "Press any key to start the test." << std::endl;
    std::cin.get();
    std::cin.get();
    size_t stdStringTookB = 0;
    size_t istringTookB   = 0;
    for (size_t i = 0; i < 10; i++)
    {
        auto [stdStringTook, istringTook]  = compare();
        stdStringTookB                    += stdStringTook;
        istringTookB                      += istringTook;
    }
    std::cout << "\033[38;2;155;155;255m" << std::endl;
    std::cout << "the mean time used by std::string is: " << stdStringTookB / 10 << std ::endl;
    std::cout << "the mean time used by istring     is: " << istringTookB / 10 << std ::endl;
    std::cout << "\033[38;2;204;204;204m";
    return 0;
}