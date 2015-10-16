// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ISolverListener.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:39:19 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 15:44:36 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISOLVERLISTENER_HPP
# define ISOLVERLISTENER_HPP

namespace npuzzle
{

class	ISolverListener
{
public:
	virtual ~ISolverListener(void) {}

	virtual void	put_progress(float progress) = 0;

protected:

private:
};

};

#endif
