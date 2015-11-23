// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SliderView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:27:39 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/23 19:26:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SLIDERVIEW_HPP
# define SLIDERVIEW_HPP

# include "ftui/Activity.hpp"
# include "ftui/ASolidView.hpp"
# include "ftui/AView.hpp"

/*
** ========================================================================== **
** SliderView
** ---
** Represent a slider that the user can scroll to change it's value
** -
** TODO: better design
** TODO: setParams
*/
class	SliderView : ftui::ASolidView
{
public:
	enum class	LuaCallback : uint32_t
	{
		VALUE_CHANGE = static_cast<uint32_t>(ftui::AView::LuaCallback::__LAST),
		__LAST
	};

	SliderView(ftui::Activity &act, ft::XmlParser const &xml);
	virtual ~SliderView(void);

	static ftui::AView	*createView(ftui::Activity &act,
							ft::XmlParser const *xml, std::string const *id);

	/*
	** Value is between bounds.x and bounds.y
	*/
	float				getValue(void) const;
	void				setValue(float val);

	/*
	** Return the value rounded by step
	** Return 0 if _steps <= 0
	*/
	int					getStepValue(void) const;

	/*
	** Number of possible value in the bounds
	** If steps is <= 0 there is an unlimited number of step
	** Warning: setSteps may change the value
	*/
	int					getSteps(void) const;
	void				setSteps(int step);

	/*
	** Bounds
	** min and max values
	*/
	ft::Vec2<float>		getBounds(void) const;
	void				setBounds(ft::Vec2<float> bounds);

	/*
	** onValueChange (lua: "view:onValueChange(value)")
	** -
	** Called everythime the value change
	** (by user action or setValue)
	** -
	** During this callback:
	** 	It's safe to call setValue(float) (it will not call onValueChange again)
	*/
	virtual void		onValueChange(float val);

	virtual void		onDraw(ftui::Canvas &canvas);

	virtual bool		onMouseDown(int x, int y, int button, int mods);
	virtual bool		onMouseUp(int x, int y, int button, int mods);
	virtual bool		onMouseMove(int x, int y);
	virtual bool		onMouseScroll(int x, int y, float delta);

	virtual void		onAttach(void);
	virtual void		onDetach(void);

	/*
	** TODO: protected
	*/
	static int			getValueG(lua_State *l);
	static int			setValueG(lua_State *l);
	static int			getStepValueG(lua_State *l);
	static int			getBoundsG(lua_State *l);
	static int			setBoundsG(lua_State *l);
	static int			getStepsG(lua_State *l);
	static int			setStepsG(lua_State *l);

protected:

	ft::Vec2<float>		_bounds;
	float				_value;
	int					_steps;

	bool				_inCallback;

	void				setValueWidth(int x);

	SliderView(ftui::Activity &act, std::string const *id,
		std::string const &viewName = "SliderView");

private:
	SliderView(void);
	SliderView(SliderView const &src);
	SliderView			&operator=(SliderView const &rhs);
};

#endif
