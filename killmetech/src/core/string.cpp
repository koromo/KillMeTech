#include "string.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <cwctype>

namespace killme
{
    std::string narrow(const std::string& s)
    {
        return s;
    }

    std::string narrow(const std::wstring& s)
    {
        const auto length = s.length();
        std::vector<char> multi(length + 1, '\0');
        std::wcstombs(multi.data(), s.data(), length);
        return multi.data();
    }

    std::wstring widen(const std::string& s)
    {
        const auto length = s.length();
        std::vector<wchar_t> wide(length + 1, L'\0');
        std::mbstowcs(wide.data(), s.data(), length);
        return wide.data();
    }

    std::wstring widen(const std::wstring& s)
    {
        return s;
    }

    std::string toLowers(const std::string& s)
    {
        std::string lowers = s;
        std::transform(std::cbegin(s), std::cend(s), std::begin(lowers), &std::tolower);
        return lowers;
    }

    std::wstring toLowers(const std::wstring& s)
    {
        std::wstring lowers = s;
        std::transform(std::cbegin(s), std::cend(s), std::begin(lowers), &std::towlower);
        return lowers;
    }

    std::string toUppers(const std::string& s)
    {
        std::string uppers = s;
        std::transform(std::cbegin(s), std::cend(s), std::begin(uppers), &std::toupper);
        return uppers;
    }

    std::wstring toUppers(const std::wstring& s)
    {
        std::wstring uppers = s;
        std::transform(std::cbegin(s), std::cend(s), std::begin(uppers), &std::towupper);
        return uppers;
    }

    int strcmpLow(const std::string& a, const std::string& b)
    {
        return std::strcmp(toLowers(a).c_str(), toLowers(b).c_str());
    }

    int strcmpLow(const std::wstring& a, const std::wstring& b)
    {
        return std::wcscmp(toLowers(a).c_str(), toLowers(b).c_str());

    }

    size_t strlen(const std::string& s)
    {
        return s.length();
    }

    size_t strlen(const std::wstring& s)
    {
        return s.length();
    }

    int vsprintf(char* buffer, const char* fmt, va_list args)
    {
        return std::vsprintf(buffer, fmt, args);
    }

    int vsprintf(wchar_t* buffer, const wchar_t* fmt, va_list args)
    {
        return std::vswprintf(buffer, fmt, args);
    }

    tstring toCharSet(const std::string& s)
    {
#ifdef KILLME_UNICODE
        return widen(s);
#else
        return s;
#endif
    }

    tstring toCharSet(const std::wstring& s)
    {
#ifdef KILLME_UNICODE
        return s;
#else
        return narrow(s);
#endif
    }
}