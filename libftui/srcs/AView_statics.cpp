// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 22:43:22 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ftui/AView.hpp"
#include "ftui/VerticalLayout.hpp"

namespace ftui
{

AView::views_info_t				AView::viewsInfo
{
	{"AView", AView::view_info_s{"", nullptr, std::vector<AView::view_info_s::luamethod_t>{
				std::make_tuple("setRequestedSize", &AView::setRequestedSizeG),
					std::make_tuple("setAlpha", &AView::setAlphaG),
					std::make_tuple("setVisibility", &AView::setVisibilityG),
					std::make_tuple("setParam", &AView::setParamG),
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
