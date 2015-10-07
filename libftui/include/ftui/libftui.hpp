// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libftui.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/07 20:50:34 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIBFTUI_H
# define LIBFTUI_H

# include "ft/assert.hpp"

namespace ftui
{

class	Activity;
class	IEventBox;
template<class T, typename... Args>	class EventBox;
class	IEventParams;
template<typename... Args>			class EventParams;
template<typename... Args>			class DefaultEventBox;

class	Canvas;

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

/*
** Glfw binding
*/
class GlfwWindow;
class IGlfwEventListener;

void			lua_pushUtils(Activity const &a);

};

#endif
