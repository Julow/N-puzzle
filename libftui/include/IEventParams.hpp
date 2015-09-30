// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IEventParams.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:51:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 09:56:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IEVENTPARAMS_HPP
# define IEVENTPARAMS_HPP

class ftui::IEventParams
{
protected:
	IEventParams(){};
	virtual ~IEventParams(){};
private:
	IEventParams(IEventParams const &) = delete;
	IEventParams				&operator=(IEventParams const &) = delete;
};

#endif // ************************************************** IEVENTPARAMS_HPP //
