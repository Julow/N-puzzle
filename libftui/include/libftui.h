/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/29 06:45:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTUI_H
# define LIBFTUI_H

namespace ftui
{
	
class	Activity;
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

template <typename T> class	Vec2;
template <typename T> class	Vec3;

};

#endif
