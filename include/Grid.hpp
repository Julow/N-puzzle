// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/26 13:41:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRID_HPP
# define GRID_HPP

# include <string>
# include <vector>

# include "ftlua/push.hpp"

# define MAX_GRID_SIZE		999
# define MIN_GRID_SIZE		2

class	Grid
{
public:
	static Grid const	def; // TODO: c pa ici ke sa doi etr

	Grid(void);
	Grid(int size);
	Grid(int const* const* data, int size);
	Grid(std::string const &fileName);

	Grid(Grid const &src);
	Grid(Grid &&src);
	Grid				&operator=(Grid const &rhs);
	Grid				&operator=(Grid &&rhs);

	~Grid(void);
    operator ftlua::Converter<Grid const>() const;

	std::string const	&getName(void) const;
	void				setName(std::string const &name);

	int					**getData(void);
	int const* const*	getData(void) const;

	int					getSize(void) const;

	int					get(int x, int y) const;
	int					&get(int x, int y);

	void				set(int x, int y, int v);

	void				convert(std::vector<int> const &table);

protected:

	std::string			_name;

	int					**_data;
	int					_size;

	void				alloc(int size);

private:
};

#endif
