// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_SonInfo.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 12:47:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 14:37:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"

namespace ftui
{

AView::SonInfo::SonInfo(
	std::string const &parent, factory_t create, luamemfunsinfo_t luaMemfuns)
	: parent(parent), create(create), luaMemfuns(luaMemfuns){}

AView::SonInfo::SonInfo(AView::SonInfo::SonInfo const &src)
	: parent(src.parent), create(src.create), luaMemfuns(src.luaMemfuns){}

AView::SonInfo::SonInfo()
	: parent(""), create(nullptr), luaMemfuns(){}

AView::SonInfo::~SonInfo(void){}

AView::SonInfo		&AView::SonInfo::operator=(AView::SonInfo const &rhs)
{
	this->parent = rhs.parent;
	this->create = rhs.create;
	this->luaMemfuns = rhs.luaMemfuns;
	return (*this);
}

};
