/*	Dimensions

HiROC CVS ID: Dimensions.hh,v 1.7 2010/11/24 03:32:14 castalia Exp

Copyright (C) 2007  Arizona Board of Regents on behalf of the
Planetary Image Research Laboratory, Lunar and Planetary Laboratory at
the University of Arizona.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License, version 2.1,
as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/

#ifndef _Dimensions_
#define _Dimensions_

#include	<iosfwd>


namespace UA
{
namespace HiRISE
{
//******************************************************************************
/**	A <i>Point_2D</i> holds 2-dimensional position information.

	@author		Bradford Castalia, UA/PIRL
	@version	1.7
*/
struct Point_2D
{
//!	The horizontal (x-axis) position of the point.
int
	X;
//!	The vertical (y-axis) position of the point.
int
	Y;

/*==============================================================================
	Constructors:
*/
//!	Constructs a point at position 0,0.
Point_2D ();

//!	Constructs a point at position x,y.
Point_2D (const int& x,const int& y);

/**	Constructs a point from another point.

	@param	point	A Point_2D to be copied.
*/
Point_2D (const Point_2D& point);

/**	Assign the position of another point to this point.

	@param	point	A Point_2D whose values are to be assigned to this point.
*/
Point_2D& operator= (const Point_2D& point);

/*==============================================================================
	Accessors:
*/
/**	Get the horizontal (x-axis) position.

	@return	The horizontal (x-axis) position of the point.
*/
inline int x () const
	{return X;}

/**	Set the horizontal (x-axis) position.

	@param	x_position	The horizontal (x-axis) position of the point.
	@return	This Point_2D.
*/
inline Point_2D& x (const int& x_position)
	{X = x_position; return *this;}

/**	Get the vertical (y-axis) position.

	@return	The vertical (y-axis) position of the point.
*/
inline int y () const
	{return Y;}

/**	Set the vertical (y-axis) position.

	@param	y_position	The vertical (y-axis) position of the point.
	@return	This Point_2D.
*/
inline Point_2D& y (const int& y_position)
	{Y = y_position; return *this;}

};	//	End of Point_2D class.

/**	Print a Point_2D description to an output stream.

	@param	stream	The ostream where the Point_2D will be printed.
	@param	point	The Point_2D to be printed.
	@return	The stream that was written.
*/
std::ostream& operator<< (std::ostream& stream, const Point_2D& point);

//******************************************************************************
/**	A <i>Size_2D</i> holds 2-dimensional size information.

	@author		Bradford Castalia, UA/PIRL
	@version	1.7
*/
struct Size_2D
{
//!	The width of the 2D size.
unsigned int
	Width;
//!	The height of the 2D size.
unsigned int
	Height;

/*==============================================================================
	Constructors:
*/
/**	Constructs an empty 2D size.

	Both width and height are zero.
*/
Size_2D ();

/**	Constructs a specific size.

	@param	width	The width of the size.
	@param	height	The height of the size.
*/
Size_2D (const unsigned int& width, const unsigned int& height);

/**	Constructs a size of equal width and height.

	@param	side	The length of each side. Both width and height will
		be set to this value.
*/
Size_2D (const unsigned int& side);

/**	Constructs a size from another size.

	@param	size	A Size_2D to be copied.
*/
Size_2D (const Size_2D& size);

/**	Assign the size of another size to this size.

	@param	size	A Size_2D to have its values assigned to this size.
*/
Size_2D& operator= (const Size_2D& size);

/*==============================================================================
	Accessors:
*/
/**	Get the width of the size.

	@return	The width of the size.
*/
inline unsigned int width () const
	{return Width;}

/**	Set the width of the size.

	@param	width	The width of the size.
	@return	This Size_2D.
*/
inline Size_2D& width (const unsigned int& width)
	{Width = width; return *this;}

/**	Get the height of the size.

	@return	The height of the size.
*/
inline unsigned int height () const
	{return Height;}

/**	Set the height of the size.

	@param	height	The height of the size.
	@return	This Size_2D.
*/
inline Size_2D& height (const unsigned int& height)
	{Height = height; return *this;}

/**	Get the area of this size.

	@return	The area (width * height) of the size.
*/
inline unsigned long area () const
	{return Width * Height;}

};	//	End of Size_2D class.

/**	Print a Size_2D description to an output stream.

	@param	stream	The ostream where the Size_2D will be printed.
	@param	size	The Size_2D to be printed.
	@return	The stream that was written.
*/
std::ostream& operator<< (std::ostream& stream, const Size_2D& size);

//******************************************************************************
/**	A <i>Rectangle</i> is a position with a size.

	@author		Bradford Castalia, UA/PIRL
	@version	1.7
	@see	Point_2D
	@see	Size_2D
*/
struct Rectangle
:	public Point_2D,
	public Size_2D
{
/*==============================================================================
	Constructors:
*/
/**	Constructs an empty rectangle.

	The position is 0,0 and the size is 0,0.
*/
Rectangle ();

/**	Constructs a rectangle from a position and a size.

	@param	position	A Point_2D.
	@param	size		A Size_2D.
*/
Rectangle (const Point_2D& position, const Size_2D& size);

/**	Constructs a rectangle from a size at position 0,0.

	@param	size		A Size_2D.
*/
Rectangle (const Size_2D& size);

/**	Constructs a rectangle from an x,y position and width,height size.

	@param	x	The horizontal (x-axis) position.
	@param	y	The vertical (y-axis) position.
	@param	width	The width of the rectangle size.
	@param	height	The height of the recangle size.
*/
Rectangle
	(
	const int			x,
	const int			y,
	const unsigned int	width = 0,
	const unsigned int	height = 0
	);

/**	Constructs a rectangle as a copy of another rectangle.

	@param	rectangle	A Rectangle to be copied.
*/
Rectangle (const Rectangle& rectangle);

/**	Assign the position and size of another rectangle to this rectangle.

	@param	rectangle	A Rectangle whose position and size are be assigned
		to this rectangle.
	@return	This Rectangle.
*/
Rectangle& operator= (const Rectangle& rectangle);

/*==============================================================================
	Accessors:
*/
/**	Get the rectangle position.

	@return	A Point_2D with the rectangle position. <b>N.B.</b>: Changing
		this point will not change the position of the rectangle.
*/
inline Point_2D position () const
	{return Point_2D (X, Y);}

/**	Set the position of the rectangle.

	@param	point	A Point_2D for the position of the rectangle.
	@return	This Rectangle.
*/
inline Rectangle& position
	(
	const Point_2D&	point
	)
{
X = point.X;
Y = point.Y;
return *this;
}

/**	Set the x,y position of the rectangle.

	@param	x	The horizontal (x-axis) position.
	@param	y	The vertical (y-axis) position.
	@return	This Rectangle.
*/
inline Rectangle& position
	(
	const int	x,
	const int	y
	)
{
X = x;
Y = y;
return *this;
}

/**	Get the rectangle size.

	@return	A Size_2D with the rectangle size. <b>N.B.</b>: Changing
		this size will not change the size of the rectangle.
*/
inline Size_2D size () const
	{return Size_2D (Width, Height);}

/**	Set the size of the rectangle.

	@param	size	A Size_2D for the size of the rectangle.
	@return	This Rectangle.
*/
inline Rectangle& size
	(
	const Size_2D&	size
	)
{
Width  = size.Width;
Height = size.Height;
return *this;
}

/**	Set the width,height of the rectangle.

	@param	width	The width of the rectangle size.
	@param	height	The height of the recangle size.
	@return	This Rectangle.
*/
inline Rectangle& size
	(
	const unsigned int	width,
	const unsigned int	height
	)
{
Width = width;
Height = height;
return *this;
}

/*==============================================================================
	Manipulators:
*/
/**	Take the intersection with another rectangle.

	@param	rectangle	The Rectangle to intersect with this Rectangle.
	@return	This Rectangle with its position and size set to the
		intersection with the other rectangle. If the rectangles do not
		intersect this will result in a rectangle with no area (width
		and height both zero) but the position will be unchanged.
*/
Rectangle& operator&= (const Rectangle& rectangle);

};	//	End of Rectangle class.

/**	Print a Rectangle description to an output stream.

	@param	stream	The ostream where the Rectangle will be printed.
	@param	rectangle	The Rectangle to be printed.
	@return	The stream that was written.
*/
std::ostream& operator<< (std::ostream& stream, const Rectangle& rectangle);

}	//	namespace HiRISE
}	//	namespace UA
#endif
