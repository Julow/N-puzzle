/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
//   Updated: 2015/09/24 06:57:40 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef AVIEW_HPP
# define AVIEW_HPP

# include <string>
//# include <iostream>
//# include <stdexcept>
/*
# include "IViewHolder.hpp"
# include "ACanvas.hpp"
# include "ALayout.hpp"
*/
class ALayout;		//debug
class ACanvas;		//debug
class IViewHolder;	//debug

/**
 **	AView handles it's spacial attributes through.
 **		'_holder' functions
 **		 'onPositionChange' callback
 **		 'onSizeChange' callback
 */

class AView
{
public:
	// * NESTED OBJECTS ************* //

	/** A query is spread to parent (flag to 1 everwhere)
		A query callback is spread from parent (flag to 0 everwhere) */
	enum		Query
	{
		REDRAW_QUERY = (1 << 1),
		MEASURE_QUERY = (1 << 2),
		UPDATE_QUERY = (1 << 3),
	};

	/** A target registering is spread to parent (parent has different flags)
		A target callback is spread from parent */
	enum		Target
	{
		MOUSE_SCROLL_TARGET = (1 << 8),
		MOUSE_CLICK_TARGET = (1 << 9),
		MOUSE_POSITION_TARGET = (1 << 10),
		KEYBOARD_TARGET = (1 << 11),
	};

	/** Custom behaviours */
	enum		Misc
	{
		MOUSE_OVER = (1 << 16),
		HIDDEN = (1 << 17),
	};

	// * CTORS / DTORS ************** //
	AView();
	virtual ~AView();

protected:
	// * ATTRIBUTES ***************** //
	ALayout				*_parent;
	IViewHolder			*_holder;

	std::string const *const	_id;
	unsigned long				_flags;
	float						_alpha;

/*
** * Targetings ************************************************************** *
*/
public:
	// * FROM PARENT **************** //
	/** Called if (isMouseScrollSensivite && isMouseOver) */
	virtual void		onMouseScroll(int x, int y, float delta);
	/** Called if (isMouseClickSensivite && isMouseOver) */
	virtual bool		onMouseDown(int x, int y, int button);
	/** Called if (isMouseClickSensivite && isMouseOver)*/
	virtual bool		onMouseUp(int x, int y, int button);
	/** Called if (isMousePositionSensivite && isMouseOver) */
	virtual void		onMouseMove(int x, int y);
	/** Called if (isKeyboardSensitive) */
	virtual bool		onKeyDown(int key_code);
	/** Called if (isKeyboardSensitive) */
	virtual void		onKeyUp(int key_code);

protected:
	// * TO PARENT ****************** //
	void				registerMouseScrollTarget(bool state);
	void				registerMouseClickTarget(bool state);
	void				registerMousePositionTarget(bool state);
	void				registerKeyboardTarget(bool state);

public:
	// * SETTERS ******************** //
	// * GETTERS ******************** //
	bool				isMouseScollTarget(void) const
		{return this->_flags & AView::MOUSE_SCROLL_TARGET;}
	bool				isMouseClickTarget(void) const
		{return this->_flags & AView::MOUSE_CLICK_TARGET;}
	bool				isMousePositionTarget(void) const
		{return this->_flags & AView::MOUSE_POSITION_TARGET;}
	bool				isKeyboardTarget(void) const
		{return this->_flags & AView::KEYBOARD_TARGET;}
		
/*
** * Queries ***************************************************************** *
*/
public:
	// * FROM PARENT **************** //
	virtual void		onUpdate(void);
	virtual void		onMeasure(void);
	virtual void		onDraw(ACanvas &canvas);

protected:
	// * TO PARENT ****************** //
	void				queryRedraw(void);
	void				queryMeasure(void);
	void				queryUpdate(void);

public:
	// * SETTERS ******************** //
	// * GETTERS ******************** //
	bool				flaggedRedraw(void) const
		{return this->_flags & AView::REDRAW_QUERY;}
	bool				flaggedMeasure(void) const
		{return this->_flags & AView::MEASURE_QUERY;}
	bool				flaggedUpdate(void) const
		{return this->_flags & AView::UPDATE_QUERY;}
	
/*
** * Misc ******************************************************************** *
*/
public:
	// * CALLBACKS ****************** //
	/** Called by this->onMouseMove() */
	virtual void		onMouseEnter(void);
	/** Called by this->onMouseMove() */
	virtual void		onMouseLeave(void);
	/** Called by activity */
	virtual void		onEvent(std::string const &event);
	/** Called by parent */
	virtual void		onPositionChange(void);
	/** Called by parent */
	virtual void		onSizeChange(void);
	/** Called by this->setVisibility() */
	virtual void		onVisibilityChange(bool state);

public:
	// * GETTERS ******************** //
	std::string const	*getId(void) const
		{return this->_id;}
	float				getAlpha(void) const
		{return this->_alpha;}
	bool				isVisible(void) const
		{return this->_flags & AView::HIDDEN;}
	bool				isMouseOver(void) const
		{return this->_flags & AView::MOUSE_OVER;}
		
	// * SETTERS ******************** //
	void				setAlpha(float value);
	void				setVisibility(bool state);

protected:
	// * LOW LEVEL SETTERS ********** //
	/** Called by this->onMouseMove() */
	virtual void		setMouseOver(bool state);

	// * LOW LEVEL GETTERS ********** //
	template <typename LAYOUT>
	typename LAYOUT::ViewHolder	*getHolder(void) const
	{return dynamic_cast<typename LAYOUT::ViewHolder const*>(this->_holder);}
	template <typename LAYOUT>
	typename LAYOUT::ViewHolder	*getHolder(void)
	{return dynamic_cast<typename LAYOUT::ViewHolder*>(this->_holder);}
	

private:
	AView(AView const &src) = delete;
	AView				&operator=(AView const &rhs) = delete;
};

#endif // ********************************************************* AVIEW_HPP //
