/*
*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   This library is under the MIT license
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <unordered_map>
#include <utility>


namespace
{

inline std::basic_string<unsigned char> toUstring(const std::string& str)
{
    return std::basic_string<unsigned char>(str.begin(), str.end());
}

inline std::string toString(const std::basic_string<unsigned char>& u8str)
{
    return std::string(u8str.begin(), u8str.end());
}

// Used in utf8_find
void preprocess(const UTF8string& str,
                std::unordered_map<std::string, size_t>& u8map) noexcept
{
    const size_t U8LEN = str.utf8_length();

    // Preprocessing
    if(U8LEN > 1)
    {
        for(size_t i = U8LEN - 2U; ; --i)
        {
            const std::string& s = str[i];

            if(u8map.find(s) == u8map.end())
                u8map[s] = U8LEN - 1 - i;

            if(i == 0)
                break;
        }
    }
}

}


UTF8string::UTF8string(const char * str)
    : UTF8string(std::string(str)) {}


UTF8string::UTF8string(const std::string& str)
    : _utf8data(str.cbegin(), str.cend())
{
    if(!utf8_is_valid_())
        throw std::invalid_argument("Invalid UTF-8 string\n");

    _utf8length = utf8_length_();
    _string = str;
    _cached = true;
}


UTF8string::UTF8string(const UTF8string& u8str) noexcept
    : _utf8data(u8str._utf8data), _utf8length(u8str._utf8length),
      _string(u8str._string), _cached(u8str._cached) {}

UTF8string::UTF8string(UTF8string&& u8str) noexcept
    : _utf8data(u8str._utf8data), _utf8length(u8str._utf8length),
      _string(u8str._string), _cached(u8str._cached)
{
    u8str.utf8_clear();
    u8str._utf8data.shrink_to_fit();
    u8str._string.shrink_to_fit();
}

UTF8string& UTF8string::operator =(const char * str)
{
    const std::string S(str);
    _utf8data = std::move(toUstring(S));

    if(!utf8_is_valid_())
        throw std::invalid_argument("Invalid UTF-8 string\n");

    _utf8length = utf8_length_();
    _string = S;
    _cached = true;
    return *this;
}


UTF8string& UTF8string::operator =(const std::string& str)
{
    _utf8data = std::move(toUstring(str));

    if(!utf8_is_valid_())
        throw std::invalid_argument("Invalid UTF-8 string\n");

    _utf8length = utf8_length_();
    _string = str;
    _cached = true;
    return *this;
}


UTF8string& UTF8string::operator =(const UTF8string& u8str) noexcept
{
    _utf8data = u8str._utf8data;
    _utf8length = u8str._utf8length;
    _string = u8str._string;
    _cached = u8str._cached;
    return *this;
}

UTF8string& UTF8string::operator =(UTF8string&& u8str) noexcept
{
    _utf8data = u8str._utf8data;
    _utf8length = u8str._utf8length;
    _string = u8str._string;
    _cached = u8str._cached;

    u8str.utf8_clear();
    u8str._utf8data.shrink_to_fit();
    u8str._string.shrink_to_fit();

    return *this;
}

const UTF8string& UTF8string::operator +=(const std::string& str)
{
    UTF8string::u8string s = _utf8data;
    _utf8data += std::move(toUstring(str));

    if(!utf8_is_valid_())
    {
        _utf8data = s;
        throw std::invalid_argument("Invalid UTF-8 string\n");
    }

    _utf8length = utf8_length_();
    _cached = false;
    return *this;
}


const UTF8string& UTF8string::operator +=(const UTF8string& u8str)
{
    _utf8data  += u8str._utf8data;
    _utf8length = utf8_length_();
    _cached = false;
    return *this;
}


const UTF8string& UTF8string::operator +=(const char * str)
{
    UTF8string::u8string s = _utf8data;
    _utf8data += std::move(toUstring(std::string(str)));

    if(!utf8_is_valid_())
    {
        _utf8data = s;
        throw std::invalid_argument("Invalid UTF-8 string\n");
    }

    _utf8length = utf8_length_();
    _cached = false;
    return *this;
}


bool UTF8string::utf8_is_valid_() const noexcept
{
    auto it = _utf8data.begin();
    const auto ITEND = _utf8data.end();

    while(it < ITEND)
    {
        if((0xF8 & *it) == 0xF0 && *it <= 0xF4)
        {
            // The UTF-8 codepoint begin with 0b11110xxx -> 4-byte codepoint
            // If the iterator reach the end of the string before the
            // end of the 4-byte codepoint -> invalid string
            if((it + 1) == ITEND || (it + 2) == ITEND || (it + 3) == ITEND)
                return false;

            // Each of the following bytes is a value
            // between 0x80 and 0xBF
            if(((0xC0 & *(it + 1)) != 0x80) || ((0xC0 & *(it + 2)) != 0x80)
                    || ((0xC0 & *(it + 3)) != 0x80))
            {
                return false;
            }

            // If the first byte of the sequence is 0xF0
            // then the first continuation byte must be between 0x90 and 0xBF
            // otherwise, if the byte is 0xF4
            // then the first continuation byte must be between 0x80 and 0x8F
            if(*it == 0xF0)
            {
                if(*(it + 1) < 0x90 || *(it + 1) > 0xBF)
                    return false;
            }
            else if(*it == 0xF4)
            {
                if(*(it + 1) < 0x80 || *(it + 1) > 0x8F)
                    return false;
            }

            it += 4;    // Jump to the next codepoint
        }
        else if((0xF0 & *it) == 0xE0)
        {
            // The UTF-8 codepoint begin with 0b1110xxxx -> 3-byte codepoint
            if((it + 1) == ITEND || (it + 2) == ITEND)
                return false;

            // Each of the following bytes starts with
            // 0b10xxxxxx in a valid string
            if(((0xC0 & *(it + 1)) != 0x80) || ((0xC0 & *(it + 2)) != 0x80))
                return false;

            // If the first byte of the sequence is 0xE0
            // then the first continuation byte must be between 0xA0 and 0xBF
            // otherwise, if the byte is 0xF4
            // then the first continuation byte must be between 0x80 and 0x9F
            if(*it == 0xE0)
            {
                if(*(it + 1) < 0xA0 || *(it + 1) > 0xBF)
                    return false;
            }
            else if(*it == 0xED)
            {
                if(*(it + 1) > 0x9F)
                    return false;
            }

            it += 3;
        }
        else if((0xE0 & *it) == 0xC0)
        {
            // The UTF-8 codepoint begin with 0b110xxxxx -> 2-byte codepoint
            if((it + 1) == ITEND)
                return false;

            // The following byte starts with 0b10xxxxxx in a valid string
            if((0xC0 & *(it + 1)) != 0x80)
                return false;

            it += 2;
        }
        else if((0x80 & *it) == 0x00)
        {
            // The UTF-8 codepoint begin with 0b0xxxxxxx -> 1-byte codepoint
            it += 1;
        }
        else
        {
            // Invalid codepoint
            return false;
        }
    }

    return true;
}

// Compute the length of the utf-8 string (in number of codepoints)
size_t UTF8string::utf8_length_() const noexcept
{
    auto end_data = _utf8data.end();
    auto it = _utf8data.begin();
    size_t len = 0;

    while(it != end_data)
    {
        byte_t byte = *it;

        if (0xf0 == (0xf8 & byte))
        {
            // 4-byte utf8 character
            // (0b11110xxx 0bxxxxxxxx 0bxxxxxxxx 0bxxxxxxxx)
            it += 4;
        }
        else if (0xe0 == (0xf0 & byte))
        {
            // 3-byte utf8 code point (0b110xxxxx 0bxxxxxxxx 0bxxxxxxxx)
            it += 3;
        }
        else if (0xc0 == (0xe0 & byte))
        {
            // 2-byte utf8 code point (0b110xxxxx 0bxxxxxxxx)
            it += 2;
        }
        else
        {
            // 1-byte utf8 code point (0b0xxxxxxx)
            it += 1;
        }

        // We want the number of characters (utf-8 code point)
        len += 1;
    }

    return len;
}

// Compute the memory size of a codepoint in the string (in byte)
size_t UTF8string::utf8_codepoint_len_(const size_t j) const noexcept
{
    if (0xf0 == (0xf8 & _utf8data[j]))
    {
        return 4;
    }
    else if (0xe0 == (0xf0 & _utf8data[j]))
    {
        return 3;
    }
    else if (0xc0 == (0xe0 & _utf8data[j]))
    {
        return 2;
    }
    else
        return 1;
}


void UTF8string::utf8_clear() noexcept
{
    _utf8data.clear();
    _string.clear();
    _utf8length = 0;
    _cached = true;
}


bool UTF8string::utf8_empty() const noexcept
{
    return _utf8length == 0;
}

/*
    Get the memory position of a codepoint according
    to its position in the utf-8 string
*/
size_t UTF8string::utf8_bpos_at_(const size_t cpos) const noexcept
{
    size_t bpos = 0;
    const size_t U8SIZE = utf8_size();

    for(size_t i = 0; bpos < U8SIZE && i < cpos; i++)
    {
        bpos += utf8_codepoint_len_(bpos);
    }
    return bpos;
}


UTF8string::u8string UTF8string::utf8_at_(const size_t index) const noexcept
{
    size_t bpos    = utf8_bpos_at_(index);
    const size_t N = utf8_codepoint_len_(bpos);
    return _utf8data.substr(bpos, N);
}


std::string UTF8string::utf8_at(const size_t index) const
{
    if(index >= _utf8length)
        throw std::out_of_range("index value greater than the size of the string");

    return toString(utf8_at_(index));
}


std::string UTF8string::operator [](const size_t index) const noexcept
{
    return toString(utf8_at_(index));
}


void UTF8string::utf8_pop()
{
    if(_utf8length == 0)
        throw std::length_error("Cannot remove the last element from an empty string");

    size_t bpos = utf8_bpos_at_(_utf8length - 1);
    _utf8data.erase(bpos);
    _utf8length -= 1;

    // If the cache was valid before tis operation,
    // keep the cache valid!
    if(_cached)
        _string.erase(bpos);
}


UTF8string UTF8string::utf8_substr(size_t pos, size_t len) const
{
    if(pos > _utf8length)
        return UTF8string();

    // Length of the substring (number of code points)
    const size_t N = (len == UTF8string::npos || (pos + len) > _utf8length) ?
                     (_utf8length - pos) : len;

    UTF8iterator it = utf8_iterator_() + pos;
    const UTF8iterator _END = (it + N);
    std::string s;

    while(it != _END)
    {
        s += *(it++);
    }

    return UTF8string(s);
}

// This function implements the Boyer-Moore string search algorithm
size_t UTF8string::utf8_find(const UTF8string& str, size_t pos) const
{
    if(str._utf8length == 0)
        return UTF8string::npos;

    // Preprocessing
    std::unordered_map<std::string, size_t> u8map;
    preprocess(str, u8map);

    const size_t U8LEN = str._utf8length;
    size_t index = pos;

    // Look for the subtring
    while(index <= _utf8length - U8LEN)
    {
        size_t j = U8LEN - 1;
        bool found = false;

        while((str.utf8_at(j) == utf8_at(index + j)))
        {
            if(j == 0)
            {
                found = true;
                break;
            }

            j--;
        }

        if(!found)
        {
            std::string ss = utf8_at(index + j);
            index += (u8map.find(ss) == u8map.end()) ? U8LEN : u8map[ss];
        }
        else
            return index;
    }

    return UTF8string::npos;
}

// Tail-recursive function that reverse the string
UTF8string UTF8string::utf8_reverse_aux_(UTF8iterator& it,
        const UTF8iterator& _end,
        UTF8string& res)
{
    if(it == _end)
        return res;

    res += *(--it);
    return utf8_reverse_aux_(it, _end, res);
}


UTF8string& UTF8string::utf8_reverse()
{
    if(_utf8length > 1)
    {
        UTF8iterator it = utf8_end();
        UTF8string rev;
        _utf8data = (utf8_reverse_aux_(it, utf8_iterator_(), rev))._utf8data;
        _cached = false;
    }

    return *this;
}


size_t UTF8string::utf8_size() const noexcept
{
    return _utf8data.size();
}


size_t UTF8string::utf8_length() const noexcept
{
    return _utf8length;
}

const std::string UTF8string::utf8_sstring() const noexcept
{
    if(!_cached)
    {
        _string = std::move(toString(_utf8data));
        _cached = true;
    }
    return _string;
}

const char * UTF8string::utf8_str() const noexcept
{
    if(!_cached)
    {
        _string = std::move(toString(_utf8data));
        _cached = true;
    }
    return _string.c_str();
}

// Internal function that creates an iterator of the current string
UTF8iterator UTF8string::utf8_iterator_() const noexcept
{
    return UTF8iterator(*this);
}


UTF8iterator UTF8string::utf8_begin() const noexcept
{
    return utf8_iterator_();
}


UTF8iterator UTF8string::utf8_end() const noexcept
{
    return utf8_begin() + _utf8length;
}


UTF8iterator UTF8string::begin() const noexcept
{
    return utf8_begin();
}


UTF8iterator UTF8string::end() const noexcept
{
    return utf8_begin() + _utf8length;
}


bool operator ==(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return str1.utf8_sstring() == str2.utf8_sstring();
}

bool operator !=(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return !(str1 == str2);
}


bool operator <=(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return str1.utf8_sstring() <= str2.utf8_sstring();
}


bool operator >=(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return str1.utf8_sstring() >= str2.utf8_sstring();
}


bool operator <(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return str1.utf8_sstring() < str2.utf8_sstring();
}


bool operator >(const UTF8string& str1, const UTF8string& str2) noexcept
{
    return str1.utf8_sstring() > str2.utf8_sstring();
}


UTF8string operator +(const UTF8string& str1, const UTF8string& str2)
{
    return str1 + str2.utf8_sstring();
}


UTF8string operator +(const UTF8string& str1, const std::string& str2)
{
    return UTF8string(str1.utf8_sstring() + str2);
}

UTF8string operator +(const std::string& str1, const UTF8string& str2)
{
    return UTF8string(str1 + str2.utf8_sstring());
}


UTF8string operator +(const UTF8string& str1, const char * str2)
{
    return str1 + std::string(str2);
}


UTF8string operator +(const char * str1, const UTF8string& str2)
{
    return std::string(str1) + str2;
}


std::ostream& operator <<(std::ostream& os, const UTF8string& str)
{
    os << str.utf8_sstring();
    return os;
}


std::istream& operator >>(std::istream& is, UTF8string& str)
{
    std::string tmp;
    std::getline(is, tmp);
    str = tmp;
    return is;
}
