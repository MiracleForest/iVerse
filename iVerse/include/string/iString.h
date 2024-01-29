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
#include <codecvt>
#include <functional>
#include <iFamily.h>
#include <string>

namespace MiracleForest::inline i::inline iVerse
{
namespace String
{
    class iString
    {
    private:
        Ptr<u8char>            _data;
        size_t                 _length;
        size_t                 _begin;
        size_t                 _capacity;
        std::allocator<u8char> _alloc;

    public:
        iString(CPtr<char> dat) { _create((CPtr<u8char>)dat); }
        iString(CRef<std::string> dat) { _create((CPtr<u8char>)dat.c_str(), dat.length()); }
        iString(CPtr<u8char> dat) { _create(dat); }
        iString(CPtr<wchar> dat)
        {
            auto tempStr = std::wstring_convert<std::codecvt_utf16<wchar>>().to_bytes(dat);
            _create((CPtr<u8char>)tempStr.c_str(), tempStr.length());
        }
        ~iString() { _alloc.deallocate(_data, _capacity); }
        operator std::string() const { return operator CPtr<char>(); }
        operator CPtr<char>() const { return (CPtr<char>)(_data + _begin); }

    public:
        size_t length() const { return _length; }

    private:
        void _create(CPtr<u8char> dat)
        {
            for (_length = 0; *(dat + _length); _length++) {}
            _capacity = 2 * _length;
            _data     = _alloc.allocate(_capacity);
            _begin    = _length / 2;
            memcpy(_data + _begin, dat, _length + 1);
        }

        void _create(CPtr<u8char> dat, size_t length)
        {
            _capacity = 2 * length;
            _data     = _alloc.allocate(_capacity);
            _begin    = length / 2;
            _length   = length;
            memcpy(_data + _begin, dat, length + 1);
        }
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
        MiracleForest::CPtr<char> str  = key;
        while (*str) { hash = hash * 131 + (*str++); }
        return (hash & 0x7FFFFFFF);
    }
};
} // namespace std