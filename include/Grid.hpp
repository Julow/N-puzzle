// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 14:38:24 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRID_HPP
# define GRID_HPP

# include <string>
# include <vector>
# include <cmath> //ftlua_pop

# include "ftlua/push.hpp"

# define MAX_GRID_SIZE		999
# define MIN_GRID_SIZE		3

class	Grid
{
public:
	static Grid const	def; // TODO: c pa ici ke sa doi etr

	Grid();
	Grid(int size, std::string const &name = "noname");
	Grid(int const* const data[], int size, std::string const &name = "noname");
	Grid(std::string const &fileName);

	Grid(Grid const &src);
	Grid(Grid &&src);
	Grid				&operator=(Grid const &rhs);
	Grid				&operator=(Grid &&rhs);

	~Grid(void);

	typedef std::integral_constant<unsigned int, 1>	ftlua_size;
	void				ftlua_push(lua_State *l,
							std::function<void(std::string)> panic) const;
	static Grid			ftlua_pop(lua_State *l, int i,
							std::function<void(std::string)> panic);

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

	static Grid			ftlua_pop_helper(lua_State *l,
							std::function<void(std::string)> panic,
							int tabindex2, int w);

private:
};
std::ostream			&operator<<(std::ostream &o, Grid const &rhs);

#endif
