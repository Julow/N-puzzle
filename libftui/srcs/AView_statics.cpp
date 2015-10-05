// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 13:30:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ftui/AView.hpp"
#include "ftui/VerticalLayout.hpp"

namespace ftui
{

AView::views_info_t				AView::viewsInfo
{
	{"AView", {"", nullptr, {
				{"setRequestedSize", nullptr},
				{"setAlpha", nullptr},
				{"setVisibility", nullptr},
				{"setParam", nullptr},
					}}},
	{"ALayout", {"AView", nullptr, {}}},
	{"VerticalLayout", {"ALayout", &VerticalLayout::createView, {}}}
};

AView::view_info_s::factory_t	AView::getFactory(std::string const &name)
{
	AView::view_info_s		f;

	f = AView::viewsInfo.at(name);
	//TODO?? catch throw
	return (f.factory);
}

void							AView::registerNewSonView(
	std::string const &name
	, std::string const &parent
	, view_info_s::factory_t factory
	, std::vector<view_info_s::luamethod_t> luaMethods)
{
	if (!AView::viewsInfo.insert(
			std::make_pair(name, AView::view_info_s{parent, factory, luaMethods})
			).second)
	{
		std::cerr << "Factory, already exists" << std::endl;
		// TODO throw? static AView::registerFactory
	}
	return ;
}

};
