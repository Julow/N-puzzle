// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/22 12:57:44 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVIEW_HPP
# define AVIEW_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>

class AView
{
public:
	AView();
	AView(AView const &src);
	AView						&operator=(AView const &rhs);
	virtual ~AView();
	void						onDragStart();
	void						onDragStop();
	
protected:
private:
};

#endif // ********************************************************* AVIEW_HPP //
