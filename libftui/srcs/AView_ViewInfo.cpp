// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_ViewInfo.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:13:39 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 11:21:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"

namespace ftui
{

AView::ViewInfo::ViewInfo(factory_t create, luamemfunsinfo_t luaMemfuns)
	: create(create), luaMemfuns(luaMemfuns){}

AView::ViewInfo::ViewInfo(AView::ViewInfo::ViewInfo const &src)
	: create(src.create), luaMemfuns(src.luaMemfuns){}

AView::ViewInfo::ViewInfo()
	: create(nullptr), luaMemfuns(){}

AView::ViewInfo::~ViewInfo(void){}

AView::ViewInfo        &AView::ViewInfo::operator=(AView::ViewInfo const &rhs)
{
	this->create = rhs.create;
	this->luaMemfuns = rhs.luaMemfuns;
	return (*this);
}

};
