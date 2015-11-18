// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/18 18:06:15 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRID_HPP
# define GRID_HPP

# include <string>

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

	int					**getData(void);
	int const* const*	getData(void) const;

	int					getSize(void) const;

	int					get(int x, int y) const;
	int					&get(int x, int y);

	void				set(int x, int y, int v);

protected:

	int					**_data;
	int					_size;

	void				alloc(int size);

private:
};

#endif
