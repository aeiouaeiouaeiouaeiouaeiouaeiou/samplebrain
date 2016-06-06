/*
Copyright (c) 2006 Henry Strickland & Ryan Seto

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

        (* http://www.opensource.org/licenses/mit-license.php *)
*/

#ifndef FLX_FIXED
#define FLX_FIXED

namespace spiralcore {

class Fixed {

private:
public:
#ifdef _EE
	short g; // the guts
    const static int BP= 8;  // how many low bits are right of Binary Point
#else
	int	g; // the guts
    const static int BP= 16;  // how many low bits are right of Binary Point
#endif
    const static int BP2= BP*2;  // how many low bits are right of Binary Point
    const static int BPhalf= BP/2;  // how many low bits are right of Binary Point

    static double STEP() { return 1.0 / (1<<BP); }  // smallest step we can represent



	// for private construction via guts
	enum FixedRaw { RAW };
	Fixed(FixedRaw, int guts) : g(guts) {}

//public:

	Fixed() : g(0) {}
	Fixed(const Fixed& a) : g( a.g ) {}
	Fixed(float a) : g( int(a / (float)STEP()) ) {}
	Fixed(double a) : g( int(a / (double)STEP()) ) {}
	Fixed(int a) : g( a << BP ) {}
	Fixed(long a) : g( a << BP ) {}
	Fixed& operator =(const Fixed& a) { g= a.g; return *this; }
	Fixed& operator =(float a) { g= Fixed(a).g; return *this; }
	Fixed& operator =(double a) { g= Fixed(a).g; return *this; }
	Fixed& operator =(int a) { g= Fixed(a).g; return *this; }
	Fixed& operator =(long a) { g= Fixed(a).g; return *this; }

	operator float() const { return g * (float)STEP(); }
	operator double() const { return g * (double)STEP(); }
	operator int() const { return g>>BP; }
	operator long() const { return g>>BP; }

	Fixed operator +() const { return Fixed(RAW,g); }
	Fixed operator -() const { return Fixed(RAW,-g); }

	Fixed operator +(const Fixed& a) const { return Fixed(RAW, g + a.g); }
	Fixed operator -(const Fixed& a) const { return Fixed(RAW, g - a.g); }
#if 1
	// more acurate, using long long
	Fixed operator *(const Fixed& a) const { return Fixed(RAW,  (int)( ((long long)g * (long long)a.g ) >> BP)); }
#else
	// faster, but with only half as many bits right of binary point
	Fixed operator *(const Fixed& a) const { return Fixed(RAW, (g>>BPhalf) * (a.g>>BPhalf) ); }
#endif
	Fixed operator /(const Fixed& a) const { return Fixed(RAW, int( (((long long)g << BP2) / (long long)(a.g)) >> BP) ); }

	Fixed operator +(float a) const { return Fixed(RAW, g + Fixed(a).g); }
	Fixed operator -(float a) const { return Fixed(RAW, g - Fixed(a).g); }
	Fixed operator *(float a) const { return Fixed(RAW, (g>>BPhalf) * (Fixed(a).g>>BPhalf) ); }
	Fixed operator /(float a) const { return Fixed(RAW, int( (((long long)g << BP2) / (long long)(Fixed(a).g)) >> BP) ); }

	Fixed operator +(double a) const { return Fixed(RAW, g + Fixed(a).g); }
	Fixed operator -(double a) const { return Fixed(RAW, g - Fixed(a).g); }
	Fixed operator *(double a) const { return Fixed(RAW, (g>>BPhalf) * (Fixed(a).g>>BPhalf) ); }
	Fixed operator /(double a) const { return Fixed(RAW, int( (((long long)g << BP2) / (long long)(Fixed(a).g)) >> BP) ); }

	Fixed& operator +=(Fixed a) { return *this = *this + a; return *this; }
	Fixed& operator -=(Fixed a) { return *this = *this - a; return *this; }
	Fixed& operator *=(Fixed a) { return *this = *this * a; return *this; }
	Fixed& operator /=(Fixed a) { return *this = *this / a; return *this; }

	Fixed& operator +=(int a) { return *this = *this + (Fixed)a; return *this; }
	Fixed& operator -=(int a) { return *this = *this - (Fixed)a; return *this; }
	Fixed& operator *=(int a) { return *this = *this * (Fixed)a; return *this; }
	Fixed& operator /=(int a) { return *this = *this / (Fixed)a; return *this; }

	Fixed& operator +=(long a) { return *this = *this + (Fixed)a; return *this; }
	Fixed& operator -=(long a) { return *this = *this - (Fixed)a; return *this; }
	Fixed& operator *=(long a) { return *this = *this * (Fixed)a; return *this; }
	Fixed& operator /=(long a) { return *this = *this / (Fixed)a; return *this; }

	Fixed& operator +=(float a) { return *this = *this + a; return *this; }
	Fixed& operator -=(float a) { return *this = *this - a; return *this; }
	Fixed& operator *=(float a) { return *this = *this * a; return *this; }
	Fixed& operator /=(float a) { return *this = *this / a; return *this; }

	Fixed& operator +=(double a) { return *this = *this + a; return *this; }
	Fixed& operator -=(double a) { return *this = *this - a; return *this; }
	Fixed& operator *=(double a) { return *this = *this * a; return *this; }
	Fixed& operator /=(double a) { return *this = *this / a; return *this; }

	bool operator ==(const Fixed& a) const { return g == a.g; }
	bool operator !=(const Fixed& a) const { return g != a.g; }
	bool operator <=(const Fixed& a) const { return g <= a.g; }
	bool operator >=(const Fixed& a) const { return g >= a.g; }
	bool operator  <(const Fixed& a) const { return g  < a.g; }
	bool operator  >(const Fixed& a) const { return g  > a.g; }

	bool operator ==(float a) const { return g == Fixed(a).g; }
	bool operator !=(float a) const { return g != Fixed(a).g; }
	bool operator <=(float a) const { return g <= Fixed(a).g; }
	bool operator >=(float a) const { return g >= Fixed(a).g; }
	bool operator  <(float a) const { return g  < Fixed(a).g; }
	bool operator  >(float a) const { return g  > Fixed(a).g; }

	bool operator ==(double a) const { return g == Fixed(a).g; }
	bool operator !=(double a) const { return g != Fixed(a).g; }
	bool operator <=(double a) const { return g <= Fixed(a).g; }
	bool operator >=(double a) const { return g >= Fixed(a).g; }
	bool operator  <(double a) const { return g  < Fixed(a).g; }
	bool operator  >(double a) const { return g  > Fixed(a).g; }
};

inline Fixed operator +(float a, const Fixed& b) { return Fixed(a)+b; }
inline Fixed operator -(float a, const Fixed& b) { return Fixed(a)-b; }
inline Fixed operator *(float a, const Fixed& b) { return Fixed(a)*b; }
inline Fixed operator /(float a, const Fixed& b) { return Fixed(a)/b; }

inline bool operator ==(float a, const Fixed& b) { return Fixed(a) == b; }
inline bool operator !=(float a, const Fixed& b) { return Fixed(a) != b; }
inline bool operator <=(float a, const Fixed& b) { return Fixed(a) <= b; }
inline bool operator >=(float a, const Fixed& b) { return Fixed(a) >= b; }
inline bool operator  <(float a, const Fixed& b) { return Fixed(a)  < b; }
inline bool operator  >(float a, const Fixed& b) { return Fixed(a)  > b; }



inline Fixed operator +(double a, const Fixed& b) { return Fixed(a)+b; }
inline Fixed operator -(double a, const Fixed& b) { return Fixed(a)-b; }
inline Fixed operator *(double a, const Fixed& b) { return Fixed(a)*b; }
inline Fixed operator /(double a, const Fixed& b) { return Fixed(a)/b; }

inline bool operator ==(double a, const Fixed& b) { return Fixed(a) == b; }
inline bool operator !=(double a, const Fixed& b) { return Fixed(a) != b; }
inline bool operator <=(double a, const Fixed& b) { return Fixed(a) <= b; }
inline bool operator >=(double a, const Fixed& b) { return Fixed(a) >= b; }
inline bool operator  <(double a, const Fixed& b) { return Fixed(a)  < b; }
inline bool operator  >(double a, const Fixed& b) { return Fixed(a)  > b; }


inline int& operator +=(int& a, const Fixed& b) { a = (Fixed)a + b; return a; }
inline int& operator -=(int& a, const Fixed& b) { a = (Fixed)a - b; return a; }
inline int& operator *=(int& a, const Fixed& b) { a = (Fixed)a * b; return a; }
inline int& operator /=(int& a, const Fixed& b) { a = (Fixed)a / b; return a; }

inline long& operator +=(long& a, const Fixed& b) { a = (Fixed)a + b; return a; }
inline long& operator -=(long& a, const Fixed& b) { a = (Fixed)a - b; return a; }
inline long& operator *=(long& a, const Fixed& b) { a = (Fixed)a * b; return a; }
inline long& operator /=(long& a, const Fixed& b) { a = (Fixed)a / b; return a; }

inline float& operator +=(float& a, const Fixed& b) { a = a + b; return a; }
inline float& operator -=(float& a, const Fixed& b) { a = a - b; return a; }
inline float& operator *=(float& a, const Fixed& b) { a = a * b; return a; }
inline float& operator /=(float& a, const Fixed& b) { a = a / b; return a; }

inline double& operator +=(double& a, const Fixed& b) { a = a + b; return a; }
inline double& operator -=(double& a, const Fixed& b) { a = a - b; return a; }
inline double& operator *=(double& a, const Fixed& b) { a = a * b; return a; }
inline double& operator /=(double& a, const Fixed& b) { a = a / b; return a; }

}

#endif
