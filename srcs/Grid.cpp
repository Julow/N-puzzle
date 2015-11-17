// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:12 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 20:31:44 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Grid.hpp"
#include "Tokenizer.hpp"
#include "ft/utils.hpp"
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <array>

// ========================================================================== //
// CONSTRUCTION
//

#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()
#define DEFGRID Grid(MATRIX33I(LINE3I(0,1,2), LINE3I(3,4,5), LINE3I(6,7,8)), 3)

Grid const		Grid::def = DEFGRID; /*static*/

/*
** Token declarations
** Yes, it's ugly as fuck
*/
enum Token
{
	TOKEN_COMMENT,
	TOKEN_ENDL,
	TOKEN_SPACE,
	TOKEN_NUMBER
};

static Tokenizer::token_def_s const	gridTokens[] = {
	{{.str="#"}, Tokenizer::TOKEN_CHR1, TOKEN_COMMENT},
	{{.str="\n"}, Tokenizer::TOKEN_CHR1, TOKEN_ENDL},
	{{.f=&std::isspace}, Tokenizer::TOKEN_F, TOKEN_SPACE},
	{{.f=&std::isdigit}, Tokenizer::TOKEN_F, TOKEN_NUMBER}
};
/*
** -
*/

Grid::Grid()
	: _data(nullptr), _size(0)
{
	return ;
}

Grid::Grid(int size)
{
	alloc(size);
	return ;
}

Grid::Grid(int const* const* data, int size)
	: Grid(size)
{
	for (int i = 0; i < size; i++)
		std::memcpy(_data[i], data[i], size * sizeof(int));
	return ;
}

/*
** TODO: GridParser
** - check nl after grid_size token
** - Code is too big and ugly
*/
Grid::Grid(std::string const &fileName)
{
	std::ifstream	in(fileName);
	Tokenizer		tokenizer(gridTokens, sizeof(gridTokens) / sizeof(*gridTokens));
	int				grid_size;
	int				x;
	int				y;
	int				line;

	line = 1;
	while (tokenizer.next(in) && tokenizer.getTokenId() != TOKEN_NUMBER)
		if (tokenizer.getTokenId() == TOKEN_COMMENT
			|| tokenizer.getTokenId() == TOKEN_ENDL)
		{
			if (tokenizer.getTokenId() == TOKEN_COMMENT)
				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			line++;
		}
	if (tokenizer.getTokenId() != TOKEN_NUMBER)
	{
		if (in.eof())
			throw std::runtime_error(ft::f("%: Empty grid file", fileName));
		else
			throw std::runtime_error(ft::f("%:%: Syntax error: '%'",
				fileName, line, tokenizer.getToken()));
	}
	grid_size = std::stoi(tokenizer.getToken());
	if (grid_size < MIN_GRID_SIZE || grid_size > MAX_GRID_SIZE)
		throw std::runtime_error(ft::f("%: Grid too % (%)", fileName,
			(grid_size < MIN_GRID_SIZE) ? "small" : "big", grid_size));
	alloc(grid_size);
	x = 0;
	y = 0;
	while (tokenizer.next(in))
	{
		switch (tokenizer.getTokenId())
		{
		case TOKEN_COMMENT:
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		case TOKEN_ENDL:
			line++;
			if (x == 0)
				break ;
			if (x != grid_size)
				throw std::runtime_error(ft::f("%:%: Incomplete row (%/%)",
					fileName, line, x, grid_size));
			x = 0;
			y++;
			break ;
		case TOKEN_SPACE:
			break ;
		case TOKEN_NUMBER:
			if (x >= grid_size || y >= grid_size)
				throw std::runtime_error(ft::f("%:%: %", fileName, line,
					(x >= grid_size) ? "Row too large" : "Too many rows"));
			_data[y][x] = std::stoi(tokenizer.getToken());
			x++;
			break ;
		}
	}
	if (!in.eof())
		throw std::runtime_error(ft::f("%:%: Syntax error: '%'",
			fileName, line, tokenizer.getToken()));
	if (!(y == grid_size || (y == (grid_size - 1) && x == grid_size)))
		throw std::runtime_error(ft::f("%: Incomplete grid", fileName));
	// debug
	std::cout << "Grid " << fileName << ':' << std::endl;
	for (y = 0; y < grid_size; y++)
	{
		for (x = 0; x < grid_size; x++)
		{
			std::cout.width(2);
			std::cout << _data[y][x] << ' ';
		}
		std::cout << std::endl;
	}
	// -
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

void				Grid::alloc(int size)
{
	int			i;

	_data = new int*[size];
	_size = size;
	for (i = 0; i < size; i++)
		_data[i] = new int[size];
}
