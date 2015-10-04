// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_Son.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 12:43:19 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 12:43:19 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"

namespace ftui
{

AView::Son::Son(factory_t create, luamemfunsinfo_t luaMemfuns)
	: create(create), luaMemfuns(luaMemfuns){}

AView::Son::Son(AView::Son::Son const &src)
	: create(src.create), luaMemfuns(src.luaMemfuns){}

AView::Son::Son()
	: create(nullptr), luaMemfuns(){}

AView::Son::~Son(void){}

AView::Son		&AView::Son::operator=(AView::Son const &rhs)
{
	this->create = rhs.create;
	this->luaMemfuns = rhs.luaMemfuns;
	return (*this);
}

};
