/*	Dimensions

HiROC CVS ID: Dimensions.cc,v 1.4 2009/07/16 07:13:30 castalia Exp

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

*******************************************************************************/

#include	"Dimensions.hh"

#include	<iostream>


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	Point_2D
*/
/*==============================================================================
	Constructors
*/
Point_2D::Point_2D ()
	:	X (0),
		Y (0)
{}


Point_2D::Point_2D
	(
	const int&	x,
	const int&	y
	)
	:	X (x),
		Y (y)
{}


Point_2D::Point_2D
	(
	const Point_2D&	point
	)
	:	X (point.X),
		Y (point.Y)
{}


Point_2D&
Point_2D::operator=
	(
	const Point_2D&	point
	)
{
if (this != &point)
	{
	X = point.X;
	Y = point.Y;
	}
return *this;
}

std::ostream&
operator<<
	(
	std::ostream&		stream,
	const Point_2D&		point
	)
{
stream << point.X << "x, " << point.Y << "y";
return stream;
}

/*******************************************************************************
	Size_2D
*/
/*==============================================================================
	Constructors
*/
Size_2D::Size_2D ()
	:	Width (0),
		Height (0)
{}


Size_2D::Size_2D
	(
	const unsigned int&	width
	)
	:	Width (width),
		Height (width)
{}


Size_2D::Size_2D
	(
	const unsigned int&	width,
	const unsigned int&	height
	)
	:	Width (width),
		Height (height)
{}


Size_2D::Size_2D
	(
	const Size_2D&	size
	)
	:	Width (size.Width),
		Height (size.Height)
{}

Size_2D&
Size_2D::operator=
	(
	const Size_2D&	size
	)
{
if (this != &size)
	{
	Width  = size.Width;
	Height = size.Height;
	}
return *this;
}

std::ostream&
operator<<
	(
	std::ostream&		stream,
	const Size_2D& 		size
	)
{
stream << size.Width << "w, " << size.Height << "h";
return stream;
}

/*******************************************************************************
	Rectangle
*/
/*==============================================================================
	Constructors
*/
Rectangle::Rectangle ()
{}


Rectangle::Rectangle
	(
	const Size_2D&	size
	)
	:	Point_2D (),
		Size_2D (size)
{}


Rectangle::Rectangle
	(
	const Point_2D&	position,
	const Size_2D&	size
	)
	:	Point_2D (position),
		Size_2D (size)
{}


Rectangle::Rectangle
	(
	const int			x,
	const int			y,
	const unsigned int	width,
	const unsigned int	height
	)
	:	Point_2D (x, y),
		Size_2D (width, height)
{}


Rectangle::Rectangle
	(
	const Rectangle&	rectangle
	)
	:	Point_2D (rectangle.X, rectangle.Y),
		Size_2D (rectangle.Width, rectangle.Height)
{}


Rectangle&
Rectangle::operator=
	(
	const Rectangle&	rectangle
	)
{
if (this != &rectangle)
	{
	X = rectangle.X;
	Y = rectangle.Y;
	Width  = rectangle.Width;
	Height = rectangle.Height;
	}
return *this;
}


Rectangle&
Rectangle::operator&=
	(
	const Rectangle&	rectangle
	)
{
long
	this_right_edge  = (long)X + (long)Width,
	this_bottom_edge = (long)Y + (long)Height,
	that_right_edge  = (long)rectangle.X + (long)rectangle.Width,
	that_bottom_edge = (long)rectangle.Y + (long)rectangle.Height;
if (this_right_edge  < (long)rectangle.X ||
	that_right_edge  < (long)X ||
	this_bottom_edge < (long)rectangle.Y ||
	that_bottom_edge < (long)Y)
	//	No intersection.
	 Width =
	Height = 0;
else
	{
	if (X < rectangle.X)
		X = rectangle.X;
	if (Y < rectangle.Y)
		Y = rectangle.Y;
	if (this_right_edge  > that_right_edge)
		Width  = (unsigned int)(that_right_edge - X);
	if (this_bottom_edge > that_bottom_edge)
		Height = (unsigned int)(that_bottom_edge - Y);
	}
return *this;
}

std::ostream&
operator<<
	(
	std::ostream&		stream,
	const Rectangle& 	rectangle
	)
{
stream << (Point_2D)rectangle << ", " << (Size_2D)rectangle;
return stream;
}


}	//	namespace HiRISE
}	//	namespace UA
