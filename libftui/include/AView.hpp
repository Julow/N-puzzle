/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/22 16:10:34 by jaguillo         ###   ########.fr       */
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
		ENABLED_KEYBOARD = (1 << 7),
		MOUSE_DOWN = (1 << 8),
	};

	AView();
	virtual ~AView();

/*
** High level callbacks
*/
	virtual void		onMouseEnter(void);
	virtual void		onMouseLeave(void);

	virtual void		onClick(void);

	virtual void		onKeyPress(int key_code);

	virtual void		onEvent(std::string const &event);

/*
** Low level callbacks
*/
	virtual Vec2<int>	onMeasure(void);
	virtual void		onUpdate(void); // ENABLED_*

	virtual void		onDraw(ACanvas &canvas);

	virtual void		onMouseMove(int x, int y);
	virtual void		onMouseWheel(float delta);

	virtual void		onMouseUp(void);
	virtual bool		onMouseDown(int x, int y);

	virtual void		onKeyUp(int key_code);
	virtual bool		onKeyDown(int key_code);

/*
** Useless
*/
	virtual void		setVisibility(bool visi);

	bool				isVisible(void);
	bool				isMouseDown(void);

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
