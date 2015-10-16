// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 18:34:43 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Grid.hpp"
#include <cstring>

namespace npuzzle
{

Grid::Grid(int size) :
	_data(nullptr),
	_size(size)
{
	int			i;

	_data = new int*[size + 1];
	for (i = 0; i < size; i++)
		_data[i] = new int[size];
	_data[i] = NULL;
}

Grid::Grid(int const* const* data, int size) :
	Grid(size)
{
	std::memcpy(_data, data, size * size * sizeof(int));
}

Grid::~Grid(void)
{
	for (int i = 0; i < _size; i++)
		delete [] _data[i];
	delete [] _data;
}

int					**Grid::getData(void)
{
	return (_data);
}

int const* const*	Grid::getData(void) const
{
	return (_data);
}

int					Grid::getSize(void) const
{
	return (_size);
}

int					Grid::get(int x, int y) const
{
	return (_data[x][y]);
}

int					&Grid::get(int x, int y)
{
	return (_data[x][y]);
}

};
