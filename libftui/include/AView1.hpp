/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/22 18:57:07 by jaguillo         ###   ########.fr       */
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
		MOUSE_DOWN = (1 << 2),
	};
	enum		Query
	{
		QUERY_REDRAW = (1 << 1),
		QUERY_MEASURE = (1 << 2),
		QUERY_UPDATE = (1 << 3),
	};
	enum		ActivationsDeMerde
	{
		ENABLED_MOUSE = (1 << 1),
		ENABLED_KEYBOARD = (1 << 2),
	};

	AView();
	virtual ~AView();

	std::string const	*getId(void) const;

	virtual void		setVisibility(bool visi);

	bool				isVisible(void);
	bool				isMouseDown(void);

	bool				isMouseEnabled(void);
	bool				isKeyboardEnabled(void);

/*
** Request
*/
	void				requestDimension(Vec2<int> d);

protected:

	std::string const * const	_id;

	ALayout				*_parent;
	IViewHolder			*_holder;

	long				_flags;
	long				_queries;
	long				_active;

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
	virtual void		onMouseMove(int x, int y);
	virtual void		onMouseWheel(float delta);

	virtual void		onMouseUp(void);
	virtual bool		onMouseDown(int x, int y);

	virtual void		onKeyUp(int key_code);
	virtual bool		onKeyDown(int key_code);

/*
** Recursive callbacks
*/
	virtual void		onDraw(ACanvas &canvas);

	virtual void		onSizeChange(void);
	virtual void		onMeasure(void){return _holder.setRequestedDimension();}

	virtual void		onUpdate(void); // ENABLED_*

/*
** Query
*/
/*
	void				setFlagHidden(bool b);		//set que lui, call setflagredraw			util, state, pas important, a moi
	void				setFlagsMouseDown(bool b);	//set que lui, ses parents se sont deja actives

	void				setFlagsRedraw(void);		//set lui, et ses parents	query
	void				setFlagsMeasure(void);		//set lui, et ses parents
	void				setFlagsUpdate(void);		//set lui, et ses parents

	void				setFlagsEnableMouse(bool b);//set lui, et ses parents, set son activity		activer une feature enable
	void				setFlagsKeyboard(bool b);	//set lui, et ses parents, set son activity		activer une feature	enable
*/
	void				queryRedraw(void);
	void				queryMeasure(void);
	void				queryUpdate(void);

	void				enableMouse(bool e);
	void				enableKeyboard(bool e);

private:
	AView(AView const &src);
	AView				&operator=(AView const &rhs);
};

#endif // ********************************************************* AVIEW_HPP //
