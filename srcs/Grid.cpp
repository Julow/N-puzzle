// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/26 13:41:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <array>
#include <cmath>

#include "ft/assert.hpp"
#include "ft/utils.hpp"

#include "Grid.hpp"
#include "GridParser.hpp"

// ========================================================================== //
// CONSTRUCTION
//

#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()
#define DEFGRID Grid(MATRIX33I(LINE3I(0,1,2), LINE3I(3,4,5), LINE3I(6,7,8)), 3)

Grid const		Grid::def = DEFGRID; /*static*/

Grid::Grid() :
	_name(),
	_data(nullptr),
	_size(0)
{
	return ;
}

Grid::Grid(int size) :
	_name()
{
	alloc(size);
	return ;
}

Grid::Grid(int const* const* data, int size) :
	Grid(size)
{
	for (int i = 0; i < size; i++)
		std::memcpy(_data[i], data[i], size * sizeof(int));
	return ;
}

Grid::Grid(std::string const &fileName) :
	_name(fileName),
	_data(nullptr),
	_size(0)
{
	GridParser			parser(fileName);
	int					grid_size;
	int					x;
	int					y;

	grid_size = -1;
	x = 0;
	y = 0;
	while (true)
		switch (parser.next())
		{
		case GridParser::Token::ENDL:
			if (x > 0)
			{
				FTASSERT(grid_size > 0);
				if (x != grid_size)
					parser.error(ft::f("Incomplete row (%/%)", x, grid_size));
				y++;
				x = 0;
			}
			break ;
		case GridParser::Token::NUMBER:
			if (grid_size == -1)
			{
				grid_size = parser.getIntToken();
				if (grid_size < MIN_GRID_SIZE || grid_size > MAX_GRID_SIZE)
					parser.error(ft::f("Grid too % (%)",
						(grid_size < MIN_GRID_SIZE) ? "small" : "big",
						grid_size));
				alloc(grid_size);
				if (parser.next() != GridParser::Token::ENDL)
					parser.error(ft::f("Unexpected token: %",
						parser.getStrToken()));
				break ;
			}
			if (x >= grid_size || y >= grid_size)
				parser.error((x >= grid_size) ? "Row too large" : "Too many rows");
			_data[y][x] = parser.getIntToken();
			x++;
			break ;
		case GridParser::Token::END_OF_FILE:
			if (!(y == grid_size || (y == (grid_size - 1) && x == grid_size)))
				parser.error("Incomplete grid");
			// debug
			// std::cout << "Grid " << fileName << ':' << std::endl;
			// for (y = 0; y < grid_size; y++)
			// {
			// 	for (x = 0; x < grid_size; x++)
			// 	{
			// 		std::cout.width(2);
			// 		std::cout << _data[y][x] << ' ';
			// 	}
			// 	std::cout << std::endl;
			// }
			// -
			return ;
		}
}

Grid::Grid(Grid const &src) :
	Grid(src._data, src._size)
{
	_name = src._name;
	return ;
}

Grid::Grid(Grid &&src) :
	_name(std::move(src._name)), _data(src._data), _size(src._size)
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
	_name = rhs._name;
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
	_name = std::move(rhs._name);
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

Grid::operator ftlua::Converter<Grid const>() const
{
	return ftlua::Converter<Grid const>(
		*this, [](lua_State *l, Grid const &gr)
		{
			int const   w = gr.getSize();

			lua_createtable(l, w * w, 0);
			for (int i = 0; i < w * w; i++)
			{
				lua_pushinteger(l, i);
				lua_pushinteger(l, gr.get(i % w, i / w));
				lua_settable(l, -3);
			}
			return 1;
		});
}

std::string const	&Grid::getName(void) const
{
	return (_name);
}

void				Grid::setName(std::string const &name)
{
	_name = name;
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

void				Grid::convert(std::vector<int> const &table)
{
	FTASSERT((int)table.size() == this->_size * this->_size);
	for (int y = 0; y < _size; y++)
		for (int x = 0; x < _size; x++)
			this->_data[y][x] = table[this->_data[y][x]];
	return ;
}

void				Grid::alloc(int size)
{
	int			i;

	_data = new int*[size];
	_size = size;
	for (i = 0; i < size; i++)
		_data[i] = new int[size];
}
