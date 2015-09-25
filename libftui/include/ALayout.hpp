/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 11:52:27 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "libftui.h"

# include <iterator>
# include <vector>

# include "AView.hpp"

namespace ftui
{

class	ALayout : public AView, private std::vector<AView*>
{
public:
	virtual ~ALayout(void);

	virtual void				addView(AView *view);
	virtual AView				*popView(std::vector<AView*>::iterator view);

	virtual void				inflate(XmlParser &xml);

	using std::vector<AView*>::begin;
	using std::vector<AView*>::end;
	using std::vector<AView*>::cbegin;
	using std::vector<AView*>::cend;

	using std::vector<AView*>::at;
	using std::vector<AView*>::operator[];

	using std::vector<AView*>::empty;
	using std::vector<AView*>::size;

/*
** Callbacks override
*/
	virtual void				onUpdate(void) = 0;
	virtual void				onMeasure(void) = 0;
	virtual void				onDraw(ACanvas &canvas) = 0;

	virtual bool				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button);
	virtual bool				onMouseUp(int x, int y, int button);
	virtual bool				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code);
	virtual bool				onKeyUp(int key_code);

	virtual bool				isMouseScollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMousePositionTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

/*
** Target spread
*/
	void						spreadTargetMouseScroll(bool state);
	void						spreadTargetMouseClick(bool state);
	void						spreadTargetMousePosition(bool state);
	void						spreadTargetKeyboard(bool state);


protected:

	ALayout(XmlParser const &xml);

	unsigned long				_layoutFlags;

	using std::vector<AView*>::push_back;
	using std::vector<AView*>::erase;

	virtual IViewHolder			*createHolder(XmlParser const &xml
											  , ALayout *p, AView *v) = 0;
public:

private:

	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;
};

};

#endif
