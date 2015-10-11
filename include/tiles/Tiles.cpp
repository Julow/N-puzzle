// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:58:44 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 12:38:24 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream> //d
#include <cmath>
#include <cfenv>
#include "Tiles.hpp"
#include "gl.hpp"

static ft::Vec2<int>	calc_gridDim(ft::Vec2<int> const rectSize
									 , ft::Vec2<int> const triangleSize
									 , int const pointRandomRange)
{
	ft::Vec2<int>	gridDim;

	std::fesetround(FE_UPWARD);
	gridDim.x = std::lrint(
		static_cast<float>(rectSize.x + pointRandomRange * 2) / triangleSize.x);
	gridDim.y = std::lrint(
		static_cast<float>(rectSize.y + pointRandomRange * 2) / triangleSize.y);
	// gridDim.x = std::lrint(static_cast<float>(rectSize.x + pointRandomRange)
	// 					   / triangleSize.x) + 1;
	// gridDim.y = std::lrint(static_cast<float>(rectSize.y + pointRandomRange)
	// 					   / triangleSize.y) + 1;
	return gridDim;
}

static ft::Vec2<int>	calc_gridOffsets(ft::Vec2<int> const rectSize
										 , ft::Vec2<int> const triangleSize
										 , ft::Vec2<int> const gridDim)
{
	ft::Vec2<int>	gridOffsets;

	gridOffsets.x = (gridDim.x * triangleSize.x - rectSize.x) / 2;
	gridOffsets.y = (gridDim.y * triangleSize.y - rectSize.y) / 2;
	return gridOffsets;
}


Tiles::tmp_grid_t		Tiles::_build_tmp_grid(ft::Vec2<int> const gridDim)
{
	tmp_grid_t	grid;

	return grid;
}

// * CONSTRUCTORS *********************************************************** //
Tiles::Tiles(ft::Vec2<int> const rectSize
			 , ft::Vec2<int> const triangleSize /* = ... */
			 , int const pointRandomRange /* = ... */)
{
	std::cout << "[Tiles](ft::Vec2<int>) Ctor called" << std::endl;
	ft::Vec2<int> const		gridDim(
		calc_gridDim(rectSize, triangleSize, pointRandomRange));
	ft::Vec2<int> const		gridOffsets(
		calc_gridOffsets(rectSize, triangleSize, gridDim));
	std::cout << "rectSize: " << rectSize << std::endl;
	std::cout << "triangleSize :" << triangleSize << std::endl;
	std::cout << "pointRandomRange :" << pointRandomRange << std::endl;
	std::cout << "gridDim: " << gridDim << std::endl;
	std::cout << "gridOffsets: " << gridOffsets << std::endl;
	
	tmp_grid_t const		grid(this->_build_tmp_grid(gridDim));

	return ;
}


// * DESTRUCTORS ************************************************************ //
Tiles::~Tiles()
{
	std::cout << "[Tiles]() Dtor called" << std::endl;

	
	
	return ;
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //

void						Tiles::render(void)
{
	return ;
}

