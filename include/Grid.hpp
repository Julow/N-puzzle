// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/02 16:55:32 by ngoguey          ###   ########.fr       //
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
    operator ftlua::Converter<Grid const>() const;


	typedef std::integral_constant<unsigned int, 1>	ftlua_size;
	bool				ftlua_push(lua_State *l) const
		{
			int const	w = this->_size;

			lua_createtable(l, w * w, 0);
			for (int i = 0; i < w * w; i++)
			{
				lua_pushinteger(l, i);
				lua_pushinteger(l, this->_data[i / w][i % w]);
				lua_settable(l, -3);
			}
			return true;
		}


	static Grid			helper(lua_State *l, bool &err, int tabindex2, int w)
		{
			Grid		gr = Grid(w, "From_lua");

			for (int y = 0; y < w; y++)
			{
				for (int x = 0; x < w; x++)
				{
					ftlua::push(l, y * w + x);
					if (lua_gettable(l, tabindex2) != LUA_TNUMBER)
					{
						err = true;
						return Grid(0);
					}
					gr.set(x, y, lua_tointeger(l, -1));
					lua_pop(l, 1);
				}
			}
			return gr;
		}
	static Grid			ftlua_pop(lua_State *l, int i, bool &err)
		{
			int			len;
			int const	tabindex2 = i < 0 ? i - 1 : i;
			int			type;
			int			w;

			if (!lua_istable(l, i))
			{
				err = true;
				return Grid(0);
			}
			ftlua::push(l, 0);
			type = lua_gettable(l, tabindex2);
			if (type == LUA_TNIL)
				len = 0;
			else if (type == LUA_TNUMBER)
				len = 1 + luaL_len(l, tabindex2);
			else
			{
				lua_pop(l, 1);
				err = true;
				return Grid(0);
			}
			lua_pop(l, 1);
			w = static_cast<int>(sqrt(static_cast<float>(len)));
			if (w * w != len)
			{
				err = true;
				return Grid(0);
			}
			return helper(l, err, tabindex2, w);
		}


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
std::ostream			&operator<<(std::ostream &o, Grid const &rhs);

#endif
