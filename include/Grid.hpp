// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Grid.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:56:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 18:33:45 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRID_HPP
# define GRID_HPP

namespace npuzzle
{

class	Grid
{
public:
	Grid(int size);
	Grid(int const* const* data, int size);
	~Grid(void);

	int					**getData(void);
	int const* const*	getData(void) const;

	int					getSize(void) const;

	int					get(int x, int y) const;
	int					&get(int x, int y);

protected:

	int					**_data;
	int					_size;

private:
	Grid(void);
	Grid(Grid const &src);
	Grid				&operator=(Grid const &rhs);
};

};

#endif
