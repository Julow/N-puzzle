/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultEventBox.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 11:09:06 by ngoguey           #+#    #+#             */
//   Updated: 2015/10/04 16:20:28 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTEVENTBOX_HPP
# define DEFAULTEVENTBOX_HPP

# include "ftui/IEventBox.hpp"

template<typename... Args>
class ftui::DefaultEventBox : public IEventBox
{
private:
	typedef std::tuple<Args...>		tuple_t;

	AView				*_v;

public:

	DefaultEventBox(AView *v) : _v(v) {}
	virtual ~DefaultEventBox(){};

	bool				call(std::string const &ev, IEventParams *param)
		{
			return (this->_v->onEvent(ev, param));
		}

	AView const          *getView(void) const
		{
			return (this->_v);
		}
	
private:
	DefaultEventBox() = delete;
	DefaultEventBox(DefaultEventBox const &) = delete;
	DefaultEventBox					&operator=(DefaultEventBox const &) = delete;
};

#endif // ****************************************************** EVENTBOX_HPP //
