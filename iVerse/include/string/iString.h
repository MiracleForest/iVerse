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
        Ptr<u8char>            mData;
        size_t                 mLength;
        size_t                 mBegin;
        size_t                 mCapacity;
        std::allocator<u8char> mAlloc;

    public:
        iString(CPtr<char> dat) { _create((CPtr<u8char>)dat); }
        iString(CRef<std::string> dat) { _create((CPtr<u8char>)dat.c_str(), dat.length()); }
        iString(CPtr<u8char> dat) { _create(dat); }
        iString(CPtr<wchar> dat)
        {
            auto tempStr = std::wstring_convert<std::codecvt_utf16<wchar>>().to_bytes(dat);
            _create((CPtr<u8char>)tempStr.c_str(), tempStr.length());
        }
        ~iString() { mAlloc.deallocate(mData, mCapacity); }
        operator std::string() const { return operator CPtr<char>(); }
        operator CPtr<char>() const { return (CPtr<char>)(mData + mBegin); }

    public:
        size_t length() const { return mLength; }

    private:
        void _create(CPtr<u8char> dat)
        {
            mLength   = _calculateLength(dat);
            mCapacity = 2 * mLength;
            mData     = mAlloc.allocate(mCapacity);
            mBegin    = mLength / 2;
            memcpy(mData + mBegin, dat, mLength + 1);
        }

        void _create(CPtr<u8char> dat, size_t length)
        {
            mCapacity = 2 * length;
            mData     = mAlloc.allocate(mCapacity);
            mBegin    = length / 2;
            mLength   = length;
            memcpy(mData + mBegin, dat, length + 1);
        }

        constexpr static std::size_t _calculateLength(CPtr<u8char> arg)
        {
            std::size_t length = 0;
            while (*arg++) { length++; }
            return length;
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