// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 11:52:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ftui/AView.hpp"
#include "ftui/VerticalLayout.hpp"

namespace ftui
{

AView::views_info_t			AView::_views_info
{
	{"VerticalLayout", {&VerticalLayout::createView, {
				{"setRequestedSize", nullptr},
				{"setAlpha", nullptr},
				{"setVisibility", nullptr},
				{"setParam", nullptr},
	}}}
};

AView::ViewInfo::factory_t	AView::getFactory(std::string const &name)
{
	AView::ViewInfo		f;

	f = AView::_views_info.at(name);
	//TODO?? catch throw
	return (f.create);
}

void						AView::registerNewView(
	std::string const &name
	, ViewInfo::factory_t factory
	, ViewInfo::luamemfunsinfo_t luaMemFuns)
{	
	if (!AView::_views_info.insert(
			std::make_pair(name, AView::ViewInfo(factory, luaMemFuns))).second)
	{
		std::cerr << "Factory, already exists" << std::endl;
		// TODO throw? static AView::registerFactory
	}
	return ;
}

};
