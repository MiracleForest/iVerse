/****
 *
 * Copyright(C) 2022-2024 MiracleForest Studio. All Rights Reserved.
 *
 * @Filename: iString.h
 * @CreationTime: 2024.1.19.20:24
 * @Creator: Lovelylavender4
 * -----------------------------------------------------------------------------
 * Defined the iString class,
 * which aims to provide faster and more convenient methods for operations compared to std::string,
 * as well as encoding-related methods.
 * -----------------------------------------------------------------------------
 * If you discover any bugs,
 * you can provide feedback to us on GitHub or via email at MiracleForest@Outlook.com!
 * We will definitely strive to do better!
 *
 ****/
#pragma once

#include <aliases.h>
#include <functional>
#include <iFamily.h>
#include <string>
#include <vector>

namespace MiracleForest::inline i::inline iVerse
{
namespace String
{
    class iString : public std::string
    {
    private:
        Ptr<u8char>            mData;
        size_t                 mLength;
        size_t                 mBegin;
        size_t                 mCapacity;
        std::allocator<u8char> mAlloc;

    public:
        iString()
            : std::string() {};
        iString(const char* const _Ptr)
            : std::string(_Ptr) {};
        iString(const std::allocator<char>& _Al)
            : std::string(_Al) {};
        iString(std::string&& _Right)
            : std::string(_Right) {};
        iString(const std::string& _Right)
            : std::string(_Right) {};
        iString(std::initializer_list<char> _Ilist, const std::allocator<char>& _Al)
            : std::string(_Ilist, _Al) {};
        iString(std::string&& _Right, const std::allocator<char>& _Al)
            : std::string(_Right, _Al) {};
        iString(const char* const _Ptr, const std::allocator<char>& _Al)
            : std::string(_Ptr, _Al) {};
        iString(const std::string& _Right, const std::allocator<char>& _Al)
            : std::string(_Right, _Al) {};
        iString(const size_t _Count, const char _Ch)
            : std::string(_Count, _Ch) {};
        iString(const char* const _Ptr, const size_t _Count)
            : std::string(_Ptr, _Count) {};
        iString(const size_t _Count, const char _Ch, const std::allocator<char>& _Al)
            : std::string(_Count, _Ch, _Al) {};
        iString(const char* const _Ptr, const size_t _Count, const std::allocator<char>& _Al)
            : std::string(_Ptr, _Count, _Al) {};
        iString(const std::string& _Right, const size_t _Roff, const std::allocator<char>& _Al)
            : std::string(_Right, _Roff, _Al) {};
        iString(
            const std::string&          _Right,
            const size_t                _Roff,
            const size_t                _Count,
            const std::allocator<char>& _Al
        )
            : std::string(_Right, _Roff, _Count, _Al) {};

    public:
        iString& replace(CRef<iString> oldString, CRef<iString> newString, size_t times = std::string::npos)
        {
            size_t move = newString.length();
            if (oldString.empty()) { move++; }
            size_t pos = 0;
            while ((pos = find(oldString.data(), pos)) != std::string::npos && times-- != 0)
            {
                basic_string::replace(pos, oldString.length(), newString.data());
                pos += move;
            }
            return *this;
        }
        std::vector<iString> split(CRef<iString> delimiter, bool pushEmpty = false)
        {
            std::vector<iString> result;
            size_t               start = 0;
            size_t               end   = find(delimiter);

            while (end != std::string::npos)
            {
                if (delimiter.empty() && start == end) { end++; }

                // 提取子字符串（不包括分隔符）
                std::string token = substr(start, end - start);
                if (!token.empty() || pushEmpty) { result.push_back(token); }


                // 跳过分隔符
                start = end + delimiter.size();
                end   = find(delimiter, start);
            }

            // 添加最后一个子字符串（可能没有分隔符）
            if (start < size()) { result.push_back(substr(start)); }

            return result;
        }

    private:
    };
} // namespace String
} // namespace MiracleForest::inline i::inline iVerse

namespace std
{
template<>
struct hash<MiracleForest::String::iString>
{
    size_t operator()(MiracleForest::CRef<MiracleForest::String::iString> key)
    {
        MiracleForest::uint       hash = 0;
        MiracleForest::CPtr<char> str  = key.data();
        while (*str) { hash = hash * 131 + (*str++); }
        return (hash & 0x7FFFFFFF);
    }
};
} // namespace std