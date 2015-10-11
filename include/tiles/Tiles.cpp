// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:58:44 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 14:04:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream> //d
#include <cmath>
#include <cfenv>
#include "Tiles.hpp"
#include "gl.hpp"


// Tiles::tmp_grid_t		Tiles::_build_tmp_grid(ft::Vec2<int> const gridDim)
// {
// 	tmp_grid_t	grid;

// 	return grid;
// }

// * CONSTRUCTORS *********************************************************** //
Tiles::Tiles(ft::Vec2<int> const rectSize
			 , ft::Vec2<int> const triangleSize /* = ... */
			 , int const pointRandomRadius /* = ... */
			 , float const percentGray /* = ... */
			 , ft::Vec3<int> const gray /* = ... */
			 , ft::Vec3<int> const pink /* = ... */
			 , ft::Vec3<int> const deltaPink /* = ... */)
{
	std::cout << "[Tiles](ft::Vec2<int>) Ctor called" << std::endl;
	Tmp			tmp(
		rectSize, triangleSize, pointRandomRadius
		, static_cast<int>(percentGray * 100)
		, ft::Vec3<float>(gray.x, gray.y, gray.z)
		, ft::Vec3<float>(pink.x, pink.y, pink.z)
		, ft::Vec3<float>(deltaPink.x, deltaPink.y, deltaPink.z)
		);

	std::cout << "rectSize: " << tmp.rectSize << std::endl;
	std::cout << "triangleSize: " << tmp.triangleSize << std::endl;
	std::cout << "pointRandomRadius: " << tmp.pointRandomRadius << std::endl;
	std::cout << "gridDim: " << tmp.gridDim << std::endl;
	
	return ;
}
Tiles::Tmp::Tmp(ft::Vec2<int> const rectSize
				, ft::Vec2<int> const triangleSize
				, int const pointRandomRadius
	            , int const percentGray
	            , ft::Vec3<float> const gray
	            , ft::Vec3<float> const pink
	            , ft::Vec3<float> const deltaPink)
	: rectSize(rectSize)
	, triangleSize(triangleSize)
	, pointRandomRadius(pointRandomRadius)
	, percentGray(percentGray)
	, gray(gray)
	, pink(pink)
{
	_buildGridDim();
	_buildGrid();
	return ;
}

Tiles::~Tiles() { return ; }
Tiles::Tmp::~Tmp() { return ; }

// * MEMBER FUNCTIONS / METHODS ********************************************* //

void				Tiles::Tmp::_buildGridDim(void)
{
	std::fesetround(FE_UPWARD);
	gridDim.x = std::lrint(static_cast<float>(rectSize.x + pointRandomRadius * 2)
						   / triangleSize.x) + 1;
	gridDim.y = std::lrint(static_cast<float>(rectSize.y + pointRandomRadius * 2)
						   / triangleSize.y) + 1;
	return ;
}

void				Tiles::Tmp::_buildGrid(void)
{
	ft::Vec2<float>			v;
	ft::Vec2<float> const	center(static_cast<float>(rectSize.x) / 2.f,
								   static_cast<float>(rectSize.y) / 2.f);
	ft::Vec2<float> const	scale(2.f / static_cast<float>(rectSize.x),
								  2.f / static_cast<float>(rectSize.y));

	this->grid.resize(this->gridDim.y);
	for (auto &it : this->grid)
		it.resize(this->gridDim.x, point_t());
	v.y = -this->pointRandomRadius;
	for (auto &line : this->grid)
	{
		v.x = -this->pointRandomRadius;
		for (auto &point : line)
		{
			point.first = (v + _pointDeltaPos() - center) * scale;
			if (std::rand() % 100 < this->percentGray)
				point.second = gray;
			else
				point.second = pink + _pointDeltaPink();
			// std::cout
			// 	<< point.first
			// 	<< ((fabs(point.first.x) < 1.f) && (fabs(point.first.y) < 1.f))
			// 	<< std::endl;
			// std::cout << point.second << std::endl;
			
			v.x += this->triangleSize.x;
		}
		std::cout <<  std::endl;
		v.y += this->triangleSize.y;
	}
	
	return ;
}

ft::Vec2<float>		Tiles::Tmp::_pointDeltaPos(void)
{
	float const	angle = static_cast<float>(std::rand() % 360) / 180.f * M_PI;
	
	return (ft::Vec2<float>(
				cos(angle) * static_cast<float>(this->pointRandomRadius)
				, sin(angle) * static_cast<float>(this->pointRandomRadius)
				));
}

ft::Vec3<float>		Tiles::Tmp::_pointDeltaPink(void)
{	
	return (
		ft::Vec3<float>(
			deltaPink * (static_cast<float>(std::rand() % 256) / 256.f - 0.5f))
		);
}

void				Tiles::render(void)
{
	return ;
}

