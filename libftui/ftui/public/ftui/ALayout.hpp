// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/10 18:52:21 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "ftui/libftui.hpp"

# include <iterator>
# include <vector>
# include <stdint.h>

# include "ftui/ASolidView.hpp"

namespace ftui
{

/*
** ALayout
** -
** Base class for view container
** -
** Default implementation of some callbacks just spread it to childs
*/
class	ALayout : public ASolidView
{
public:

	ALayout(XmlParser const &xml, Activity &act);
	virtual ~ALayout(void);

	virtual void				addView(AView *v) = 0;
	virtual AView				*popView(AView *v) = 0;

/*
** * AView legacy *********************************************************** **
*/
	virtual void				inflate(XmlParser &xml, Activity &);

	virtual void				onUpdate(void) = 0;
	virtual void				onMeasure(void) = 0;
	virtual void				onDraw(Canvas &canvas) = 0;

	virtual bool				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button, int mods);
	virtual bool				onMouseUp(int x, int y, int button, int mods);
	virtual bool				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code, int mods);
	virtual bool				onKeyUp(int key_code, int mods);
	virtual void				onMouseLeave(int x, int y);

	virtual bool				isMouseScrollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMouseMoveTargeted(void) const;
	virtual bool				isMouseCaptureTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

	virtual bool				isUpdateQueried(void) const;
	virtual bool				isMeasureQueried(void) const;
	virtual bool				isRedrawQueried(void) const;

	virtual void				queryUpdate(void);
	virtual void				queryMeasure(void);
	virtual void				queryRedraw(void);

/*
** Child vector
*/
	virtual AView				*at(int i) = 0;
	virtual AView const			*at(int i) const = 0;

	virtual int					size(void) const = 0;

/*
** Target spread
*/
	void						spreadTargetMouseScroll(bool state);
	void						spreadTargetMouseClick(bool state);
	void						spreadTargetMouseMove(bool state);
	void						spreadTargetMouseCapture(bool state);
	void						spreadTargetKeyboard(bool state);

/*
** Query spread
*/
	void						spreadQueryUpdate(void);
	void						spreadQueryMeasure(void);
	void						spreadQueryRedraw(void);

protected:

	uint32_t					_layoutFlags;

	virtual IViewHolder			*holderAt(int i) = 0;

private:

	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;

/*
** Static
*/
public:
	static int					setParamG(lua_State *l);
	static int					atG(lua_State *l);

	static int					sizeG(lua_State *l);

	static int					addViewG(lua_State *l);
	static int					popViewG(lua_State *l);

};

};

#endif