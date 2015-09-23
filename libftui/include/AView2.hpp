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

# include <string>
//# include <iostream>
//# include <stdexcept>

# include "IViewHolder.hpp"
# include "ACanvas.hpp"
# include "ALayout.hpp"

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
		MOUSE_CAPTURE_TARGET = (1 << 11),
		KEYBOARD_TARGET = (1 << 12),
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
	long				_flags;
	float				_alpha;

/*
** * Targetings ************************************************************** *
*/
public:
	// * FROM PARENT **************** //
	/** Called if (isMouseScrollSensivite && isMouseOver) */
	virtual void		onMouseScroll(int x, int y, float delta);
	/** Called if (isMouseClickSensivite && isMouseOver) */
	virtual bool		onMouseDown(int x, int y, int button);
	/** Called if (isMouseClickSensivite && isMouseOver) || (isMouseCaptured) */
	virtual bool		onMouseUp(int x, int y, int button);
	/** Called if (isMousePositionSensivite && isMouseOver) || isMo0useCaptured*/
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
	void				registerMouseCaptureTarget(bool state);
	void				registerKeyboardTarget(bool state);

public:
	// * SETTERS ******************** //
	// * GETTERS ******************** //
	bool				isMouseScollTarget(void) const;
	bool				isMouseClickTarget(void) const;
	bool				isMousePositionTarget(void) const;
	bool				isMouseCapturedTarget(void) const;
	bool				isKeyboardTarget(void) const;

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
	bool				needsRedraw(void) const;
	bool				needsMeasure(void) const;
	bool				needsUpdate(void) const;

/*
** * Misc ******************************************************************** *
*/
public:
	/** Called by parent before (onMouseMove) & after setMouseOver(true) */
	virtual void		onMouseEnter(void);
	/** Called by parent instead of (onMouseMove) & after setMouseOver(false) */
	virtual void		onMouseLeave(void);
	/** Called by activity */
	virtual void		onEvent(std::string const &event);
	virtual void		onPositionChange(void);
	virtual void		onSizeChange(void);
	virtual void		onVisibilityChange(bool state);

public:
	// * GETTERS ******************** //
	std::string const	*getId(void) const;
	float				getAlpha(void) const;
	bool				isVisible(void) const;
	bool				isMouseOver(void) const;

	// * SETTERS ******************** //
	void				setAlpha(float value);
	void				setVisibility(bool state);

	/** Called by parent before a potential onMouseMove */
	virtual void		setMouseOver(bool state);

private:
	AView(AView const &src);
	AView				&operator=(AView const &rhs);
};

#endif // ********************************************************* AVIEW_HPP //
