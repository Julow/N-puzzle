/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
//   Updated: 2015/10/02 13:04:27 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "ftui/libftui.hpp"

# include <iterator>
# include <vector>

# include "ftui/AView.hpp"

namespace ftui
{

/*
** ALayout
** -
** Base class for view container
** -
** Default implementation of some callbacks just spread it to childs
*/
class	ALayout : public AView
{
public:

	ALayout(XmlParser const &xml, Activity &act);
	virtual ~ALayout(void);

	virtual void				addView(AView *v) = 0;
	virtual AView				*popView(AView *v) = 0;

/*
** * AView legacy *********************************************************** **
*/
	virtual void				inflate(XmlParser &xml, Activity &a);

	virtual void				setParam(std::string const &k,
									std::string const &v);

	virtual void				onUpdate(void) = 0;
	virtual void				onMeasure(void) = 0;
	virtual void				onDraw(ACanvas &canvas) = 0;

	virtual bool				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button);
	virtual bool				onMouseUp(int x, int y, int button);
	virtual bool				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code);
	virtual bool				onKeyUp(int key_code);

	virtual bool				isMouseScrollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMouseMoveTargeted(void) const;
	virtual bool				isMouseCaptureTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

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
	void						spreadTargetMove(bool state);
	void						spreadTargetMouseCapture(bool state);
	void						spreadTargetKeyboard(bool state);

protected:

	unsigned long				_layoutFlags;

	virtual IViewHolder			*holderAt(int i) = 0;

private:

	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;
};

};

#endif