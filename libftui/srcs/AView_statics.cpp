// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 14:42:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ftui/AView.hpp"
#include "ftui/VerticalLayout.hpp"

namespace ftui
{

AView::sons_info_t			AView::viewsInfo
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

AView::SonInfo::factory_t	AView::getFactory(std::string const &name)
{
	AView::SonInfo		f;

	f = AView::viewsInfo.at(name);
	//TODO?? catch throw
	return (f.create);
}

void						AView::registerNewSonView(
	std::string const &name
	, std::string const &parent
	, SonInfo::factory_t factory
	, SonInfo::luamemfunsinfo_t luaMemFuns)
{
	if (!AView::viewsInfo.insert(
			std::make_pair(
				name, AView::SonInfo(parent, factory, luaMemFuns))).second)
	{
		std::cerr << "Factory, already exists" << std::endl;
		// TODO throw? static AView::registerFactory
	}
	return ;
}

};
