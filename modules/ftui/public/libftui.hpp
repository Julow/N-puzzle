// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libftui.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/24 13:28:24 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIBFTUI_H
# define LIBFTUI_H

# include "ft/assert.hpp"

namespace ftui
{

/*
** libftui
*/

/*
** ========================================================================== **
** AView inheritance
** -
** AView							# Base class
** 	->	ASolidView					# Base class for views with a background
** 		->	SolidView				# Simplest concrete View
** 		->	TextView				# Draw text
** 		->	SliderView				# Slider
** 		->	...
** 		->	ALayout					# Base class for layouts
** 			->	HorizontalLayout
** 			->	VerticalLayout
** 				-> ScrollableLayout	# (TODO)
** 			->	AbsoluteLayout		# (TODO)
** 			->	RelativeLayout		# (TODO)
*/

/*
** ========================================================================== **
** Layout
** -
** Store and order a set of views (it's childs)
** (also dispatch events to it's childs)
** -
** Inside a layout, each childs are associated to a view holder
** 												(impl of IViewHolder)
** -
** Implemented layouts:
** 	VerticalLayout			# Order it's childs vertically
** 	HorizontalLayout		# Order it's childs horizontally
*/

/*
** ========================================================================== **
** Callbacks
** -
** C++	Callback are virtual members and can be overriden,
** 		their default implentation is to call the registered lua function
** Lua	Callback are functions that have to be registered like this:
** 			<view_table>:setCallback("<callback_name>", <callback function>)
** 		The view table is accessible inside the function by using 'self' keyword
*/

/*
** ========================================================================== **
** Params (xml)
** -
** Params are set when the view is inflating
** Of course, params can be set during runtime
** -
** Any implementation of setParam() should call AView::setParam()
**  (only if the param is inexploitable)
**  in order to handle correctly all params
**  so AView::setParam() can call it's view holder's setParam()
*/

/*
** ========================================================================== **
** Lua methods
** -
** -- ACanvas
** ACanvas:drawRect(left:int, top:int, right:int, bottom:int, fillColor:int,
** 				strokeColor:int = 0, lineWidth:int = 0)
** ACanvas:drawText(text:str, x:int, y:int, color:int, fontSize:int)
** ACanvas:measureText(text:str, fontSize:int)
** ACanvas:setFont(file_name:str)
*/

/*
** ========================================================================== **
*/

class	Activity;
class	EventTarget;
template <class T, class ...Args>		class	EventTargetCpp;
// class	IEventBox;
// template<class T, typename... Args>	class EventBox;
// class	IEventParams;
// template<typename... Args>			class EventParams;
// template<typename... Args>			class DefaultEventBox;

class	ACanvas;

class	AView;
class	SliderView;
class	TextView;

class	IViewHolder;

class	ALayout;
class	AbsoluteLayout;
class	RelativeLayout;
class	VerticalLayout;

};

#endif
