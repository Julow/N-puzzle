// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DefaultEventBox.tpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 09:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/13 09:40:27 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ftui
{

template<typename... Args>
DefaultEventBox<Args...>::DefaultEventBox(AView *v) :
	_v(v)
{
}

template<typename... Args>
DefaultEventBox<Args...>::~DefaultEventBox(void)
{
}

template<typename... Args>
bool		DefaultEventBox<Args...>::call(std::string const &ev,
				IEventParams *param)
{
	return (this->_v->onEvent(ev, param));
}

template<typename... Args>
AView const	*DefaultEventBox<Args...>::getView(void) const
{
	return (this->_v);
}

};
