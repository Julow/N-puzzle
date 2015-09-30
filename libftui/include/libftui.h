/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 11:54:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTUI_H
# define LIBFTUI_H

#include "ft/assert.hpp"

namespace ftui
{
	
class	Activity;
class	IEventBox;
template<class T, typename... ARGS> class EventBox;
class	IEventParams;
template<typename... ARGS>			class EventParams;
template<typename... ARGS>			class DefaultEventBox;

class	ACanvas;

class	AView;
class	SliderView;
class	TextView;

class	IViewHolder;

class	ALayout;
class	AbsoluteLayout;
class	RelativeLayout;
class	VerticalLayout;

class	XmlTokenizer;
class	XmlParser;	

template <typename T>				class Vec2;
template <typename T>				class Vec3;

};

#endif
