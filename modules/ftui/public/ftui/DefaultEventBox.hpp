// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DefaultEventBox.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 11:09:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 14:22:26 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DEFAULTEVENTBOX_HPP
# define DEFAULTEVENTBOX_HPP

# include "ftui/IEventBox.hpp"

namespace ftui
{

template<typename... Args>
class DefaultEventBox : public IEventBox
{
public:
	DefaultEventBox(AView *v);
	virtual ~DefaultEventBox(void);

	bool				call(std::string const &ev, IEventParams *param);

	AView const			*getView(void) const;

protected:
	AView				*_v;
	
private:
	DefaultEventBox(void) = delete;
	DefaultEventBox(DefaultEventBox const &) = delete;
	DefaultEventBox		&operator=(DefaultEventBox const &) = delete;
};

};

# include "ftui/templates/DefaultEventBox.tpp"

#endif
