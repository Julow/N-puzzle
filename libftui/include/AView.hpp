/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/22 15:26:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVIEW_HPP
# define AVIEW_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>

# include "IViewHolder.hpp"
# include "ACanvas.hpp"
# include "ALayout.hpp"

class AView
{
public:
	enum		Flags
	{
		HIDDEN = (1 << 1),
		REQUEST_REDRAW = (1 << 2),
		REQUEST_MEASURE = (1 << 3),
		REQUEST_UPDATE = (1 << 4),
		ENABLED_MOUSE = (1 << 5),
		ENABLED_KEYBOARD = (1 << 6),
	};

	AView();
	virtual ~AView();

/*
** High level callbacks
*/
	void				onMouseEnter(void);
	void				onMouseLeave(void);

	void				onClick(void);

	void				onKeyPress(int key_code);

/*
** Low level callbacks
*/
	Vec2<int>			onMeasure(void);
	void				onUpdate(void); // ENABLED_*

	void				onDraw(ACanvas &canvas);

	void				onMouseMove(int x, int y);

	void				onMouseUp(void);
	bool				onMouseDown(int x, int y);

	void				onKeyUp(int key_code);
	bool				onKeyDown(int key_code);

/*
** Useless
*/
	void				show(void);
	void				hide(void);

	bool				isVisible(void);

/*
** Request
*/
	void				requestRedraw(void);
	void				requestMeasure(void);
	void				requestUpdate(void);

protected:

	ALayout				*_parent;
	IViewHolder			*_holder;

	long				_flags;

private:
	AView(AView const &src);
	AView				&operator=(AView const &rhs);
};

#endif // ********************************************************* AVIEW_HPP //
