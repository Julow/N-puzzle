// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/13 09:00:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream> //debug

#include "ft/utils.hpp"
#include "ftui/AView.hpp"
#include "ftui/VerticalLayout.hpp"
#include "ftui/SolidView.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/TextView.hpp"

namespace ftui
{

AView::views_info_t				AView::viewsInfo
{
	{"AView", {"", nullptr, {
		std::make_tuple("setRequestedSize", &AView::setRequestedSizeG),
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
		std::make_tuple("getRequestedSize", &AView::getRequestedSizeG),
		std::make_tuple("getPos", &AView::getPosG),
		std::make_tuple("getSize", &AView::getSizeG),
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
	{"ASolidView", {"AView", nullptr, {
		std::make_tuple("getBackgroundColor", &ASolidView::getBackgroundColorG),
		std::make_tuple("getBorderColor", &ASolidView::getBorderColorG),
		std::make_tuple("getBorderWidth", &ASolidView::getBorderWidthG),
		std::make_tuple("setBackgroundColor", &ASolidView::setBackgroundColorG),
		std::make_tuple("setBorderColor", &ASolidView::setBorderColorG),
		std::make_tuple("setBorderWidth", &ASolidView::setBorderWidthG),
	}}},
	{"TextView", {"ASolidView", &TextView::createView, {
		std::make_tuple("getText", &TextView::getTextG),
		std::make_tuple("setText", &TextView::setTextG),
		std::make_tuple("getFont", &TextView::getFontG),
		std::make_tuple("setFont", &TextView::setFontG),
		std::make_tuple("getTextColor", &TextView::getTextColorG),
		std::make_tuple("setTextColor", &TextView::setTextColorG),
		std::make_tuple("getTextSize", &TextView::getTextSizeG),
		std::make_tuple("setTextSize", &TextView::setTextSizeG),
	}}},
	{"ALayout", {"ASolidView", nullptr, {
		// std::make_tuple("setParam", &ALayout::setParamG) // CHECK HERITAGE
		std::make_tuple("size", &ALayout::sizeG),
		std::make_tuple("at", &ALayout::atG)
		// std::make_tuple("addView", &ALayout::addViewG),
		// std::make_tuple("popView", &ALayout::popViewG)
	}}},
	{"VerticalLayout", {"ALayout", &VerticalLayout::createView, {}}},
	{"SolidView", {"ASolidView", &SolidView::createView, {}}},
};

AView::view_info_s::factory_t	AView::getFactory(std::string const &name)
{
	AView::view_info_s		f;

	f = AView::viewsInfo.at(name);
	return (f.factory);
}

/*
** TODO: improve this system
** TODO: move a part of this in the Activity
**        to allow user to define view after Activity init
*/
void							AView::defineView(
	std::string const &name,
	std::string const &parent,
	view_info_s::factory_t factory,
	std::vector<view_info_s::luamethod_t> luaMethods)
{
	if (!AView::viewsInfo.insert(std::make_pair(name,
		AView::view_info_s{parent, factory, luaMethods})).second)
		throw std::domain_error(ft::f("View % already defined", name));
	return ;
}

};
