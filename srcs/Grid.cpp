// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 14:19:31 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Grid.hpp"
#include "ft/utils.hpp"
#include <cstring>
#include <stdexcept>
#include <array>

// ========================================================================== //
// CONSTRUCTION
//

#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()
#define DEFGRID Grid(MATRIX33I(LINE3I(0,1,2), LINE3I(3,4,5), LINE3I(6,7,8)), 3)

Grid const		Grid::def = DEFGRID; /*static*/

Grid::Grid()
	: _data(nullptr), _size(0)
{
	return ;
}

Grid::Grid(int size)
	: _data(nullptr), _size(size)
{
	int			i;

	_data = new int*[size];
	for (i = 0; i < size; i++)
		_data[i] = new int[size];
	return ;
}

Grid::Grid(int const* const* data, int size)
	: Grid(size)
{
	for (int i = 0; i < size; i++)
		std::memcpy(_data[i], data[i], size * sizeof(int));
	return ;
}

Grid::Grid(std::string const &fileName) :
	Grid(Grid::def) //TODO: Grid from fileName (parsing beton)
{
	(void)fileName;
	return ;
}


Grid::Grid(Grid const &src) :
	Grid(src._data, src._size)
{
	return ;
}

Grid::Grid(Grid &&src) :
	_data(src._data), _size(src._size)
{
	src._data = nullptr;
	src._size = 0;
	return ;
}

Grid			&Grid::operator=(Grid const &rhs)
{
	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
			delete [] _data[i];
		delete [] _data;
	}
	this->_size = rhs._size;
	_data = new int*[_size];
	for (int i = 0; i < _size; i++)
		_data[i] = new int[_size];
	for (int i = 0; i < _size; i++)
		std::memcpy(_data[i], rhs._data[i], _size * sizeof(int));
	return *this;
}

Grid			&Grid::operator=(Grid &&rhs)
{
	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
			delete [] _data[i];
		delete [] _data;
	}
	_size = rhs._size;
	_data = rhs._data;
	rhs._size = 0;
	rhs._data = nullptr;
	return *this;
}


Grid::~Grid(void)
{
	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
			delete [] _data[i];
		delete [] _data;
	}
	return ;
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
	return (_data[y][x]);
}

void				Grid::set(int x, int y, int v)
{
	_data[y][x] = v;
	return ;
}
