/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/24 06:48:08 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AView.hpp"


AView::AView(void)
	: _parent(nullptr)
	, _holder(nullptr)
	, _id(nullptr)
	, _flags(0)
	, _alpha(0.f)
{
}

AView::~AView(void)
{
}
