// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 15:14:11 by ngoguey          ###   ########.fr       //
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
		// std::make_tuple("setRequestedSize", &AView::setRequestedSizeG),
		std::make_tuple("setAlpha", &AView::setAlphaG),
		std::make_tuple("setVisibility", &AView::setVisibilityG),
		std::make_tuple("setParam", &AView::setParamG),
		std::make_tuple("hookMouseScroll", &AView::hookMouseScrollG),
		std::make_tuple("hookMouseClick", &AView::hookMouseClickG),
		std::make_tuple("hookMouseMove", &AView::hookMouseMoveG),
		std::make_tuple("hookMouseCapture", &AView::hookMouseCaptureG),
		std::make_tuple("hookKeyboard", &AView::hookKeyboardG),
		std::make_tuple("queryUpdate", &AView::queryUpdateG),
		std::make_tuple("queryMeasure", &AView::queryMeasureG),
		std::make_tuple("queryRedraw", &AView::queryRedrawG),
		// std::make_tuple("getRequestedSize", &AView::getRequestedSizeG),
		// std::make_tuple("getPos", &AView::getPosG),
		// std::make_tuple("getSize", &AView::getSizeG),
		std::make_tuple("getId", &AView::getIdG),
		std::make_tuple("getParent", &AView::getParentG),
		std::make_tuple("getAlpha", &AView::getAlphaG),
		std::make_tuple("isVisible", &AView::isVisibleG),
		std::make_tuple("isMouseOver", &AView::isMouseOverG),
		std::make_tuple("isMouseScrollTargeted"
						, &AView::isMouseScrollTargetedG),
		std::make_tuple("isMouseClickTargeted", &AView::isMouseClickTargetedG),
		std::make_tuple("isMouseCaptureTargeted"
						, &AView::isMouseCaptureTargetedG),
		std::make_tuple("isKeyboardTargeted", &AView::isKeyboardTargetedG),
		std::make_tuple("isUpdateQueried", &AView::isUpdateQueriedG),
		std::make_tuple("isMeasureQueried", &AView::isMeasureQueriedG),
		std::make_tuple("isRedrawQueried", &AView::isRedrawQueriedG),
	}}},
	{"ALayout", {"AView", nullptr, {
		// std::make_tuple("setParam", &ALayout::setParamG) // CHECK HERITAGE
		std::make_tuple("size", &ALayout::sizeG)
		// std::make_tuple("at", &ALayout::atG),
		// std::make_tuple("addView", &ALayout::addViewG),
		// std::make_tuple("popView", &ALayout::popViewG)
			}}},
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
