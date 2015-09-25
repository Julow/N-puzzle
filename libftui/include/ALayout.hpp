/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 15:47:18 by ngoguey          ###   ########.fr       //
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

class	ALayout : public AView, private std::vector<IViewHolder*>
{
public:

	typedef std::vector<IViewHolder*>	child_container_t;

/*
** * AView legacy *********************************************************** **
*/
	virtual void				inflate(XmlParser &xml);

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

	virtual bool				isMouseScollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMousePositionTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

/*
** * ALayout new functions ************************************************** **
*/
	ALayout(XmlParser const &xml);
	virtual ~ALayout(void);

	virtual void				addView(AView *v);
	virtual AView				*popView(AView *v);

/*
** std::vector visibility management
*/
	using child_container_t::begin;
	using child_container_t::end;
	using child_container_t::cbegin;
	using child_container_t::cend;

	using child_container_t::at;
	using child_container_t::operator[];

	using child_container_t::empty;
	using child_container_t::size;

/*
** Target spread
*/
	void						spreadTargetMouseScroll(bool state);
	void						spreadTargetMouseClick(bool state);
	void						spreadTargetMousePosition(bool state);
	void						spreadTargetKeyboard(bool state);

protected:

	unsigned long				_layoutFlags;

	// using child_container_t::push_back;
	// using child_container_t::erase;

	virtual IViewHolder			*createHolder(XmlParser const &xml
											  , ALayout *p, AView *v) = 0;
	virtual IViewHolder			*createHolder(ALayout *p, AView *v) = 0;

private:

	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;
};

};

#endif
