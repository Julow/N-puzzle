// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_SonInfo.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 12:47:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 12:47:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"

namespace ftui
{

AView::SonInfo::SonInfo(factory_t create, luamemfunsinfo_t luaMemfuns)
	: create(create), luaMemfuns(luaMemfuns){}

AView::SonInfo::SonInfo(AView::SonInfo::SonInfo const &src)
	: create(src.create), luaMemfuns(src.luaMemfuns){}

AView::SonInfo::SonInfo()
	: create(nullptr), luaMemfuns(){}

AView::SonInfo::~SonInfo(void){}

AView::SonInfo		&AView::SonInfo::operator=(AView::SonInfo const &rhs)
{
	this->create = rhs.create;
	this->luaMemfuns = rhs.luaMemfuns;
	return (*this);
}

};
