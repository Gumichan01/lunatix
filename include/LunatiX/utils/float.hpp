
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   This library is under the MIT license
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef FLOAT_HPP
#define FLOAT_HPP

struct Float
{
    float v;
    // static_cast<float>(Float)
    operator float() const;
};

Float operator -(const Float& x);
Float& operator ++(Float& x);
Float operator ++(Float& x, int);
Float& operator --(Float& x);
Float operator --(Float& x, int);

Float operator +(const Float x, const Float y);
Float operator -(const Float x, const Float y);
Float operator *(const Float x, const Float y);
Float operator /(const Float x, const Float y);

Float operator +(const Float x, float y);
Float operator -(const Float x, float y);
Float operator *(const Float x, float y);
Float operator /(const Float x, float y);

Float& operator +=(Float& x, const Float y);
Float& operator -=(Float& x, const Float y);
Float& operator *=(Float& x, const Float y);
Float& operator /=(Float& x, const Float y);

Float& operator +=(Float& x, float y);
Float& operator -=(Float& x, float y);
Float& operator *=(Float& x, float y);
Float& operator /=(Float& x, float y);

bool operator ==(const Float& x, const Float& y);
bool operator !=(const Float& x, const Float& y);
bool operator <(const Float& x, const Float& y);
bool operator >(const Float& x, const Float& y);
bool operator <=(const Float& x, const Float& y);
bool operator >=(const Float& x, const Float& y);

#endif // FLOAT_HPP
