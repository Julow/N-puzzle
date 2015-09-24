/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
//   Updated: 2015/09/24 14:05:19 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef AVIEW_HPP
# define AVIEW_HPP

# include "libftui.h"

# include <string>
# include <unordered_map>

namespace ftui
{

/*
** Represents an UI component
** -
** This is the base class for any UI component
*/

class	AView
{
public:
	enum	Query
	{
		REDRAW_QUERY = (1 << 1),
		MEASURE_QUERY = (1 << 2),
		UPDATE_QUERY = (1 << 3),
	};
	enum	Target
	{
		MOUSE_SCROLL_TARGET = (1 << 8),
		MOUSE_CLICK_TARGET = (1 << 9),
		MOUSE_POSITION_TARGET = (1 << 10),
		KEYBOARD_TARGET = (1 << 11),
	};
	enum	Misc
	{
		MOUSE_OVER = (1 << 16),
		HIDDEN = (1 << 17),
	};

	virtual ~AView(void);

/*
** View core
*/
	std::string const			*getId(void) const { return (this->_id); }

	ALayout						*getParent(void);

	void						setViewHolder(IViewHolder *holder);

	/*
	** View properties
	*/
	float						getAlpha(void) const { return (this->_alpha); }

	bool						isVisible(void) const { return (this->_flags & AView::HIDDEN); }
	bool						isMouseOver(void) const { return (this->_flags & AView::MOUSE_OVER); }

	void						setAlpha(float value);

	void						setVisibility(bool state);

/*
** Callbacks
*/
	/*
	** Queries callbacks
	*/
	virtual void				onUpdate(void);
	virtual void				onMeasure(void);
	virtual void				onDraw(ACanvas &canvas);

	/*
	** Low level callbacks
	*/
	virtual void				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button);
	virtual bool				onMouseUp(int x, int y, int button);
	virtual void				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code);
	virtual void				onKeyUp(int key_code);

	/*
	** High level callbacks
	*/
	virtual void				onMouseEnter(void);
	virtual void				onMouseLeave(void);
	virtual void				onEvent(std::string const &event);
	virtual void				onPositionChange(void);
	virtual void				onSizeChange(void);
	virtual void				onVisibilityChange(bool state);

/*
** Layout system
*/
	/*
	** Targets
	*/
	virtual bool				isMouseScollTargeted(void) const { return (this->_flags & AView::MOUSE_SCROLL_TARGET); }
	virtual bool				isMouseClickTargeted(void) const { return (this->_flags & AView::MOUSE_CLICK_TARGET); }
	virtual bool				isMousePositionTargeted(void) const { return (this->_flags & AView::MOUSE_POSITION_TARGET); }
	virtual bool				isKeyboardTargeted(void) const { return (this->_flags & AView::KEYBOARD_TARGET); }

	/*
	** Queries
	*/
	bool						isRedrawQueried(void) const { return (this->_flags & AView::REDRAW_QUERY); }
	bool						isMeasureQueried(void) const { return (this->_flags & AView::MEASURE_QUERY); }
	bool						isUpdateQueried(void) const { return (this->_flags & AView::UPDATE_QUERY); }

protected:

	AView(XmlParser const &xml);

/*
** View core
*/
	IViewHolder					*_holder;

	std::string const *const	_id;
	unsigned long				_flags;

	float						_alpha;

	void						setMouseOver(bool state);

	template <typename T>
	typename T::ViewHolder		*getHolder(void) const { return (dynamic_cast<typename T::ViewHolder const*>(this->_holder)); }
	template <typename T>
	typename T::ViewHolder		*getHolder(void) { return (dynamic_cast<typename T::ViewHolder*>(this->_holder)); }

/*
** Register target
** Some low level callbacks are not enabled by default
*/
	virtual void				registerTargetMouseScroll(bool state);
	virtual void				registerTargetMouseClick(bool state);
	virtual void				registerTargetMousePosition(bool state);
	virtual void				registerTargetKeyboard(bool state);

/*
** Query
** Queries a callback for the next frame
*/
	virtual void				queryRedraw(void);
	virtual void				queryMeasure(void);
	virtual void				queryUpdate(void);

/*
** Static
*/
public:

	typedef AView				*(*factory_t)(XmlParser&);
	typedef std::unordered_map<std::string, factory_t>	factory_map_t;

	static factory_t			getFactory(std::string const &name);
	static void					registerFactory(std::string const &name,
									factory_t factory);

private:

	static factory_map_t	_factories;

/*
** Disable
*/
private:
	AView(void) = delete;
	AView(AView const &src) = delete;
	AView				&operator=(AView const &rhs) = delete;
};

};

#endif // ********************************************************* AVIEW_HPP //
