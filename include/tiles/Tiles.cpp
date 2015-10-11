// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:58:44 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 13:46:29 by ngoguey          ###   ########.fr       //
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
			 , int const pointRandomRadius /* = ... */)
{
	std::cout << "[Tiles](ft::Vec2<int>) Ctor called" << std::endl;
	Tmp			tmp(rectSize, triangleSize, pointRandomRadius);

	std::cout << "rectSize: " << tmp.rectSize << std::endl;
	std::cout << "triangleSize: " << tmp.triangleSize << std::endl;
	std::cout << "pointRandomRadius: " << tmp.pointRandomRadius << std::endl;
	std::cout << "gridDim: " << tmp.gridDim << std::endl;
	
	return ;
}
Tiles::Tmp::Tmp(ft::Vec2<int> const rectSize
				  , ft::Vec2<int> const triangleSize
				  , int const pointRandomRadius)
	: rectSize(rectSize)
	, triangleSize(triangleSize)
	, pointRandomRadius(pointRandomRadius)
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
			// std::cout
			// 	<< point.first
			// 	<< ((fabs(point.first.x) < 1.f) && (fabs(point.first.y) < 1.f))
			// 	<< std::endl;
			v.x += this->triangleSize.x;
		}
		// std::cout <<  std::endl;
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

void				Tiles::render(void)
{
	return ;
}

