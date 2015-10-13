// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libftui.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/13 07:40:17 by ngoguey          ###   ########.fr       //
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
** 		->	SliderView				# (TODO)
** 		->	...
** 		->	ALayout					# Base class for layouts
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
*/

/*
** ========================================================================== **
** Params (xml)
** -
** Params are set when the view is inflating
** Of course, params can be set during runtime
** -
** Any implementation of setParam() should call AView::setParam()
**  in order to handle correctly all params
**  (only if the param is inexploitable)
** So AView::setParam() can call it's view holder's setParam()
** -
** AView		# Available to all views
**		id					(str)	View id (XML exclusive)
** 		alpha				(float)	View transparency
** 		visibility			(bool)
** 		mouse_scroll_target	(bool)
** 		mouse_click_target	(bool)
** 		mouse_move_target	(bool)
** 		keyboard_target		(bool)
** ASolidView
** 		backgroundColor		(color)	Background color
** 		borderColor			(color)	Border color
** 		borderWidth			(int)	Border width
** VerticalLayout's view holder
** 		marginTop			(int)	Extra margin with the previous view
** 		marginBottom		(int)	Extra margin with the next view
** 		verticalAlign		(enum)	LEFT, CENTER or RIGHT
** 		width				(uint)	Requested width
** 		height				(uint)	Requested height
** TextView
** 		text				(str)	Text to be render
** 		textFont			(str)	Font
** 		textColor			(color)
** 		textSize			(int)
*/

/*
** ========================================================================== **
*/

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

};

#endif
