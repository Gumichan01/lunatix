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


UTF8iterator::UTF8iterator(const UTF8string& u) noexcept
    : index(0),data(u) {}

UTF8iterator::UTF8iterator(const UTF8iterator& it) noexcept
    : index(it.index), data(it.data) {}

UTF8iterator::~UTF8iterator() {}


UTF8iterator& UTF8iterator::operator =(const UTF8iterator& it) noexcept
{
    data = it.data;
    index = it.index;
    return *this;
}


UTF8iterator& UTF8iterator::operator ++() noexcept
{
    if(index < data.utf8_length())
        index += 1;

    return *this;
}


UTF8iterator UTF8iterator::operator ++(int) noexcept
{
    UTF8iterator oldit(*this);

    if(index < data.utf8_length())
        index += 1;

    return oldit;
}


UTF8iterator& UTF8iterator::operator --() noexcept
{
    if(index > 0)
        index -= 1;

    return *this;
}


UTF8iterator UTF8iterator::operator --(int) noexcept
{
    UTF8iterator oldit(*this);

    if(index > 0)
        index -= 1;

    return oldit;
}


bool UTF8iterator::operator ==(const UTF8iterator& it) const noexcept
{
    return (index == it.index) && (data == it.data);
}


bool UTF8iterator::operator !=(const UTF8iterator& it) const noexcept
{
    return !(*this == it);
}


const std::string UTF8iterator::operator *() const noexcept
{
    return data.utf8_at(index);
}


UTF8iterator UTF8iterator::operator +(const size_t n) const noexcept
{
    UTF8iterator newit(*this);
    const size_t len = newit.data.utf8_length();

    if(newit.index + n < len)
        newit.index += n;
    else
        newit.index = len;

    return newit;
}


UTF8iterator UTF8iterator::operator -(const size_t n) const noexcept
{
    UTF8iterator newit(*this);

    if(newit.index >= n)
        newit.index -= n;
    else
        newit.index = 0;

    return newit;
}
