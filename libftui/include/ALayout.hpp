/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/24 14:56:36 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "libftui.h"
# include "AView.hpp"
# include <iterator>
# include <vector>

namespace ftui
{

class	ALayout : public AView, private std::vector<AView*>
{
public:
	virtual ~ALayout(void);

	virtual void				addView(AView *view);
	virtual AView				*popView(std::vector<AView*>::iterator view);

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
	virtual void				onUpdate(void);
	virtual void				onMeasure(void);
	virtual void				onDraw(ACanvas &canvas);

	virtual void				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button);
	virtual bool				onMouseUp(int x, int y, int button);
	virtual void				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code);
	virtual void				onKeyUp(int key_code);

	virtual bool				isMouseScollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMousePositionTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

protected:

	ALayout(XmlParser const &xml);

	unsigned long				_layoutFlags;

	using std::vector<AView*>::push_back;
	using std::vector<AView*>::erase;
	
/*
** Target and query override
*/
	virtual void				registerTargetMouseScroll(bool state);
	virtual void				registerTargetMouseClick(bool state);
	virtual void				registerTargetMousePosition(bool state);
	virtual void				registerTargetKeyboard(bool state);

	virtual void				queryRedraw(void);
	virtual void				queryMeasure(void);
	virtual void				queryUpdate(void);

private:

	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;
};

};

#endif
