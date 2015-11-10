// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   padformat.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/10 14:57:32 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/10 16:36:12 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/assert.hpp"
#include "ft/utils.hpp"
#include <vector>
#include <tuple>
#include <iostream>

namespace ft
{

std::vector<std::tuple<int, std::string, std::string>>	padstack{};
std::vector<std::string> const							colors{
	"\033[42m",
	"\033[43m",
	"\033[44m",
	"\033[45m",
	"\033[46m",
	"\033[47m",
};

static void		truncate_mid(std::string &str)
{
	str = str.substr(0, 5) + "." + str.substr(str.size() - 5, 5);
	return ;
}

static void		applywidth(
	std::string &str, unsigned int curwidth, unsigned int width)
{
	if (curwidth < width)
	{
		str += std::string(width - curwidth, ' ');
	}
	return ;
}

static std::string	build_header(void)
{
	std::string		str("");
	unsigned int	i;
	int				line;
	std::string		file;
	std::string		fun;
	std::size_t		pos;
	std::string		linestr;

	for (i = 0; i < padstack.size(); i++)
		str += colors[i % colors.size()] + "  ";
	str += "\033[0m";
	applywidth(str, padstack.size() * 2, 2 * 7);

	std::tie(line, file, fun) = padstack.back();
	pos = file.find_last_of('/');
	file = file.substr(pos + 1, file.find_last_of('.') - pos - 1);
	if (file.size() > 10)
		truncate_mid(file);
	applywidth(file, file.size(), 11);

	if (fun.size() > 10)
		truncate_mid(fun);
	applywidth(fun, fun.size(), 11);

	linestr = ft::f("%", line);
	applywidth(linestr, linestr.size(), 3);

	str += ft::f("\033[4m%\033[0m:\033[4m%\033[0m:\033[4m%\033[0m"
				 , file, fun, linestr);
	return str;
}

std::string padformat_openlvl(
	int line, std::string const &file, std::string const &function)
{
	std::string		str;

	padstack.push_back({line, file, function});
	str = build_header();
	return str;
}
void		padformat_closelvl(void)
{
	padstack.pop_back();
	return ;
}
std::string padformat_singlelvl(
	int line, std::string const &file, std::string const &function)
{
	std::string		str;
	int				lineback;
	std::string		fileback;
	std::string		funback;

	std::tie(lineback, fileback, funback) = padstack.back();
	if (file == fileback && function == funback && line > lineback)
		str = build_header();
	else
	{
		padstack.push_back({line, file, function});
		str = build_header();
		padstack.pop_back();
	}
	return str;
}

};
