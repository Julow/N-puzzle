// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 19:53:27 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Grid.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream> // TODO

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
	for (int i = 0; i < size; i++)
		std::memcpy(_data[i], data[i], size * sizeof(int));
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
	if (x >= _size || y >= _size)
		throw std::out_of_range("Unbound value for Grid::get");
	return (_data[y][x]);
}

int					&Grid::get(int x, int y)
{
	return (_data[x][y]);
}

};
