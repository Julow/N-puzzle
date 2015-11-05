// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/05 18:03:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Grid.hpp"
#include "ft/utils.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream> // TODO

namespace npuzzle
{

static int alloc_count = 0; //TODO remove all debug

Grid::Grid() :
	_data(nullptr), _size(0)
{
	std::cout << "Grid: CTOR empty (" << alloc_count << " allocs)\n";
	return ;
}

Grid::Grid(int size) :
	_data(nullptr), _size(size)
{
	int			i;

	alloc_count++;
	ft::f(std::cout, "Grid: CTOR size(%) (% allocs)\n", size, alloc_count);
	_data = new int*[size];
	for (i = 0; i < size; i++)
		_data[i] = new int[size];
	return ;
}

Grid::Grid(int const* const* data, int size) :
	Grid(size)
{
	std::cout << "Grid: CTOR data/size  \n";
	for (int i = 0; i < size; i++)
		std::memcpy(_data[i], data[i], size * sizeof(int));
	return ;
}

Grid::Grid(Grid const &src) :
	Grid(src._data, src._size)
{
	std::cout << "Grid: CTOR Copy  \n";
	return ;
}

Grid::Grid(Grid &&src) :
	_data(src._data), _size(src._size)
{
	std::cout << "Grid: CTOR Move  \n";
	src._data = nullptr;
	src._size = 0;
	return ;
}


Grid::~Grid(void)
{
	if (_size > 0)
	{
		alloc_count--;
		for (int i = 0; i < _size; i++)
			delete [] _data[i];
		delete [] _data;
		std::cout << "Grid: Dtor (" << alloc_count << " alloc left)\n";
	}
	else
		std::cout << "Grid: Dtor empty(" << alloc_count << " alloc left)\n";
	return ;
}

Grid			&Grid::operator=(Grid const &rhs)
{
	if (_size > 0)
	{
		alloc_count--;
		for (int i = 0; i < _size; i++)
			delete [] _data[i];
		delete [] _data;
	}
	alloc_count++;
	this->_size = rhs._size;
	_data = new int*[_size];
	for (int i = 0; i < _size; i++)
		_data[i] = new int[_size];
	for (int i = 0; i < _size; i++)
		std::memcpy(_data[i], rhs._data[i], _size * sizeof(int));
	return *this;
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
