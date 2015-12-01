// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScrollableLayout.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/26 16:06:28 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 19:23:09 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SCROLLABLELAYOUT_HPP
# define SCROLLABLELAYOUT_HPP

# include "ftui/LinearLayout.hpp"

namespace ftui
{

/*
** ========================================================================== **
** ScrollableLayout
** -
** Same behavior as LinearLayout + scroll
** -
*/
class	ScrollableLayout : public LinearLayout
{
public:
	enum class	LuaCallback : uint32_t
	{
		SCROLL_CHANGE = static_cast<uint32_t>(AView::LuaCallback::__LAST),
		MAX_SCROLL_CHANGE,
		__LAST
	};

	static AView			*createView(Activity &act);

	ScrollableLayout(Activity &act,
		std::string const &viewName = "ScrollableLayout");

	virtual ~ScrollableLayout(void);

	/*
	** Current scroll offset (in pixel)
	*/
	int						getScroll(void) const;
	void					setScroll(int scroll);

	/*
	** Max scroll
	*/
	int						getMaxScroll(void) const;

	/*
	** Called when the scroll change
	*/
	virtual void			onScrollChange(int scroll);
	virtual void			onMaxScrollChange(int maxScroll);

	/*
	** Extended
	*/
	virtual void			onSizeChange(ft::Vec2<int> size);

	virtual void			onDraw(ACanvas &canvas);

	virtual void			onMeasure(void);

	virtual bool			onMouseDown(int x, int y, int button, int mods);
	virtual bool			onMouseUp(int x, int y, int button, int mods);
	virtual bool			onMouseMove(int x, int y);
	virtual void			onMouseLeave(int x, int y);
	virtual bool			onMouseScroll(int x, int y, float delta);

	virtual void			onAttach(void);
	virtual void			onDetach(void);

	/*
	** Lua
	*/
	static int				getScrollG(lua_State *l);
	static int				setScrollG(lua_State *l);
	static int				getMaxScrollG(lua_State *l);

protected:

	int						_scroll;
	int						_maxScroll;

	void					setMaxScroll(int maxScroll);

private:
	ScrollableLayout(void);
	ScrollableLayout(ScrollableLayout const &src);
	ScrollableLayout		&operator=(ScrollableLayout const &rhs);
};

};

#endif
