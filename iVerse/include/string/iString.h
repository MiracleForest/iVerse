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

#include <algorithm>
#include <aliases.h>
#include <cctype>
#include <functional>
#include <iFamily.h>
#include <string>
#include <variant>
#include <vector>

namespace MiracleForest::inline i::inline iVerse
{
namespace String
{
    class iString : public std::u8string
    {
    public:
        using Index = size_t;

    public:
        enum class ReplaceExcludeType
        {
            None,
            Range,
            Index
        };

    public:
        class iStringReplaceExclude
        {
            friend iString;

        private:
            ReplaceExcludeType                           mType;
            std::variant<std::pair<Index, Index>, Index> mExclude;

        public:
            explicit iStringReplaceExclude()
                : mExclude((Index)0)
            {
                mType = ReplaceExcludeType::None;
            }
            explicit iStringReplaceExclude(Index start, Index end)
                : mExclude(std::make_pair<>(start, end))
            {
                mType = ReplaceExcludeType::Range;
            }
            explicit iStringReplaceExclude(Index itemIndex)
                : mExclude(itemIndex)
            {
                mType = ReplaceExcludeType::Index;
            }
        };

    private:
    public:
        using std::u8string::u8string;
        iString(CPtr<char> const _Right)
            : std::u8string((CPtr<char8_t>)_Right) {};
        iString(CRef<std::u8string> _Right)
            : std::u8string(_Right) {};

    public:
        operator CPtr<char>() const { return (CPtr<char>)data(); }
        operator Ptr<char>() { return (Ptr<char>)data(); }

    public:
        Ref<iString> replace(
            CRef<iString>         oldString,
            CRef<iString>         newString,
            size_t                times   = basic_string::npos,
            bool                  forward = true,
            Index                 pos     = 0,
            iStringReplaceExclude exclude = iStringReplaceExclude()
        )
        {
            Index itemIndex = 0;
            pos             = forward ? basic_string::find(oldString.data(), pos)
                                      : basic_string::rfind(oldString.data(), pos);
            while (pos != basic_string::npos && times-- != 0)
            {
                if (exclude.mType == ReplaceExcludeType::Range)
                {
                    if (pos > std::get<std::pair<Index, Index>>(exclude.mExclude).first
                        || pos + oldString.length()
                               < std::get<std::pair<Index, Index>>(exclude.mExclude).second)
                    {
                        basic_string::replace(pos, oldString.length(), newString.data());
                    }
                }
                else if (exclude.mType == ReplaceExcludeType::None)
                {
                    if (std::get<Index>(exclude.mExclude) != itemIndex++)
                    {
                        basic_string::replace(pos, oldString.length(), newString.data());
                    }
                }
                else { basic_string::replace(pos, oldString.length(), newString.data()); }
                pos = forward ? basic_string::find(
                          oldString.data(),
                          pos + newString.length() + oldString.empty() ? (Index)1 : (Index)0
                      )
                              : basic_string::rfind(
                                  oldString.data(),
                                  pos - oldString.empty() ? (Index)1 : (Index)0
                              );
            }
            return *this;
        }

        Index find(
            CRef<iString>         string,
            bool                  forward = true,
            Index                 pos     = 0,
            iStringReplaceExclude exclude = iStringReplaceExclude()
        )
        {
            Index itemIndex = 0;
            pos = forward ? basic_string::find(string.data(), pos) : basic_string::rfind(string.data(), pos);
            while (pos != basic_string::npos)
            {
                if (exclude.mType == ReplaceExcludeType::Range)
                {
                    if (pos > std::get<std::pair<Index, Index>>(exclude.mExclude).first
                        || pos + string.length() < std::get<std::pair<Index, Index>>(exclude.mExclude).second)
                    {
                        return pos;
                    }
                }
                else if (exclude.mType == ReplaceExcludeType::None)
                {
                    if (std::get<Index>(exclude.mExclude) != itemIndex++) { return pos; }
                }
                return pos;
            }
            return basic_string::npos;
        }

        size_t count(
            CRef<iString>         string,
            bool                  forward = true,
            Index                 pos     = 0,
            iStringReplaceExclude exclude = iStringReplaceExclude()
        )
        {
            size_t c         = 0;
            Index  itemIndex = 0;
            pos = forward ? basic_string::find(string.data(), pos) : basic_string::rfind(string.data(), pos);
            while (pos != basic_string::npos)
            {
                if (exclude.mType == ReplaceExcludeType::Range)
                {
                    if (pos > std::get<std::pair<Index, Index>>(exclude.mExclude).first
                        || pos + string.length() < std::get<std::pair<Index, Index>>(exclude.mExclude).second)
                    {
                        c++;
                    }
                }
                else if (exclude.mType == ReplaceExcludeType::None)
                {
                    if (std::get<Index>(exclude.mExclude) != itemIndex++) { c++; }
                }
                else { c++; }
                pos = forward
                          ? basic_string::find(
                              string.data(),
                              pos + string.length() + string.empty() ? (Index)1 : (Index)0
                          )
                          : basic_string::rfind(string.data(), pos - string.empty() ? (Index)1 : (Index)0);
            }
            return c;
        }

        Ref<iString> remove(
            CRef<iString>         string,
            size_t                times   = basic_string::npos,
            bool                  forward = true,
            Index                 pos     = 0,
            iStringReplaceExclude exclude = iStringReplaceExclude()
        )
        {
            Index itemIndex = 0;
            pos = forward ? basic_string::find(string.data(), pos) : basic_string::rfind(string.data(), pos);
            while (pos != basic_string::npos && times-- != 0)
            {
                if (exclude.mType == ReplaceExcludeType::Range)
                {
                    if (pos > std::get<std::pair<Index, Index>>(exclude.mExclude).first
                        || pos + string.length() < std::get<std::pair<Index, Index>>(exclude.mExclude).second)
                    {
                        basic_string::replace(pos, string.length(), u8"");
                    }
                }
                else if (exclude.mType == ReplaceExcludeType::None)
                {
                    if (std::get<Index>(exclude.mExclude) != itemIndex++)
                    {
                        basic_string::replace(pos, string.length(), u8"");
                    }
                }
                else { basic_string::replace(pos, string.length(), u8""); }
                pos = forward
                          ? basic_string::find(string.data(), pos + string.empty() ? (Index)1 : (Index)0)
                          : basic_string::rfind(string.data(), pos - string.empty() ? (Index)1 : (Index)0);
            }
            return *this;
        }

        Ref<iString> insert(CRef<iString> string, Index pos, bool override = false)
        {
            if (override) { basic_string::replace(pos, string.length(), string); }
            else { basic_string::replace(pos, 0, string); }
            return *this;
        }

        std::vector<iString> split(CRef<iString> delimiter, bool pushEmpty = false)
        {
            std::vector<iString> result;
            Index                start = 0;
            Index                end   = basic_string::find(delimiter);

            while (end != basic_string::npos)
            {
                if (delimiter.empty() && start == end) { end++; }

                // Extract substring (excluding delimiters).
                auto token = substr(start, end - start);
                if (!token.empty() || pushEmpty) { result.push_back(token); }

                // Skip delimiters.
                start = end + delimiter.size();
                end   = basic_string::find(delimiter, start);
            }

            // Add the last substring (may not have a delimiter).
            if (start < size()) { result.push_back(substr(start)); }

            return result;
        }

        std::string toStdString() { return (CPtr<char>)data(); }

        Ref<char8_t>  index(const size_type _Off) { return (*this)[_Off]; }
        CRef<char8_t> index(const size_type _Off) const { return (*this)[_Off]; }

        void push(CRef<iString> string) { basic_string::replace(basic_string::length(), 0, string.data()); }
        void pop(size_t count) { basic_string::replace(basic_string::length() - count, count, u8""); }

        void toUpper()
        {
            std::transform(basic_string::begin(), basic_string::end(), basic_string::begin(), std::toupper);
        }
        void toLower()
        {
            std::transform(basic_string::begin(), basic_string::end(), basic_string::begin(), std::tolower);
        }

        iString ltrim(CRef<iString> str)
        {
            iString s        = str;
            auto    notSpace = [](unsigned char ch) { return !std::isspace(ch); };
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
            return s;
        }
        iString rtrim(CRef<iString> str)
        {
            iString s        = str;
            auto    notSpace = [](unsigned char ch) { return !std::isspace(ch); };
            s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
            return s;
        }
        iString trim(CRef<iString> s) { return ltrim(rtrim(s)); }

    public:
        // Overloading from u8string::push_back
        void push_back(CRef<iString> string)
        {
            basic_string::replace(basic_string::length(), 0, string.data());
        }
        // Overloading from u8string::pop_back
        void pop_back(size_t count) { basic_string::replace(basic_string::length() - count, count, u8""); }
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
        MiracleForest::uint hash = 0;
        auto                str  = key.data();
        while (*str) { hash = hash * 131 + (*str++); }
        return (hash & 0x7FFFFFFF);
    }
};
} // namespace std