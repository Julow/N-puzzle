// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity_RootViewHolder.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 09:38:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 13:51:07 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ft_xml/XmlParser.hpp"

#include <fstream>

namespace ftui
{

Activity::RootViewHolder::RootViewHolder(Activity &act, ft::XmlParser const &xml,
		AView *v, ft::Vec2<int> s) :
	_activity(act),
	_view(v),
	_size(s)
{
	(void)xml;
}

Activity::RootViewHolder::~RootViewHolder(void)
{
}

ALayout			*Activity::RootViewHolder::getParent(void)
{
	return (nullptr);
}

ALayout const	*Activity::RootViewHolder::getParent(void) const
{
	return (nullptr);
}

AView			*Activity::RootViewHolder::getView(void)
{
	return (this->_view);
}

AView const		*Activity::RootViewHolder::getView(void) const
{
	return (this->_view);
}

ft::Vec2<int>	Activity::RootViewHolder::getPos(void) const
{
	return (ft::make_vec(0, 0));
}

ft::Vec2<int>	Activity::RootViewHolder::getSize(void) const
{
	return (this->_size);
}

void			Activity::RootViewHolder::setSize(ft::Vec2<int> size)
{
	if (size == _size)
		return ;
	_size = size;
	_view->onSizeChange(size);
}

void			Activity::RootViewHolder::setRequestedSize(ft::Vec2<int> size)
{
	_requestedSize = size;
}

ft::Vec2<int>	Activity::RootViewHolder::getRequestedSize(void) const
{
	return (_requestedSize);
}

void			Activity::RootViewHolder::setParam(std::string const &k
												   , std::string const &v)
{
	(void)k;
	(void)v;
	if (k == "activity_scripts")
		_activity.saveScriptPath(v);
	else if (k == "template_file")
	{
		std::stringstream	ss(v);
		char				buf[64];

		while (ss.getline(buf, sizeof(buf), ';'))
		{
			std::string			file_name(buf);

			if (file_name.size() == 0)
				continue ;

			std::ifstream		is(buf);

			if (!is)
				throw std::runtime_error(ft::f("Not a valid template file: %", buf));
			_activity.inflateTemplate(is);
		}
	}
	return ;
}

};
