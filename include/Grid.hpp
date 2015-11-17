// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 14:14:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRID_HPP
# define GRID_HPP

# include <string>

class	Grid
{

	/* CONSTRUCTION ***************** */
public:
	static Grid const	def;

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

private:
};

#endif
