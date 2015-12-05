// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SliderView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:27:39 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/05 18:09:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SLIDERVIEW_HPP
# define SLIDERVIEW_HPP

// # include "ftui/Activity.hpp"
# include "ftui/ASolidView.hpp"
// # include "ftui/AView.hpp"

namespace ftui
{

/*
** ========================================================================== **
** SliderView
** -
** Represent a slider that the user can scroll to change it's value
** -
** Params:
** 	value				(float)	Initial value
** 	steps				(int)	Number of step
** 	maxValue			(float)	Max value
** 	minValue			(float)	Min value
** 	barColor			(color)
** 	barBorderColor		(color)
** 	barBorderWidth		(int)
** 	disabled			(bool)	Set if the user can change the value
** -
** Callback:
** 	onValueChange		float value
** 				Called when the value change (by user interation or setValue())
*/
class	SliderView : public ASolidView
{
public:
	enum class	LuaCallback : uint32_t
	{
		VALUE_CHANGE = static_cast<uint32_t>(AView::LuaCallback::__LAST),
		__LAST
	};

	SliderView(ftui::Activity &act, std::string const &viewName = "SliderView");
	virtual ~SliderView(void);

	static AView		*createView(Activity &act);

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
	void				setStepValue(int step);

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
	** ACanvas params used to draw the slider bar
	*/
	ACanvas::Params			&getBarParams(void);
	ACanvas::Params const	&getBarParams(void) const;

	/*
	** Set if the user can change the value
	*/
	void				setDisabled(bool b);
	bool				isDisabled(void) const;

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

	/*
	** -
	*/
	virtual void		onDraw(ACanvas &canvas);

	virtual bool		onMouseDown(int x, int y, int button, int mods);
	virtual bool		onMouseUp(int x, int y, int button, int mods);
	virtual bool		onMouseMove(int x, int y);
	virtual bool		onMouseScroll(int x, int y, float delta);

	virtual void		onAttach(void);
	virtual void		onDetach(void);

	virtual void		setParam(std::string const &k,
							std::string const &v);

	/*
	** Lua C functions
	*/
	static int			getValueG(lua_State *l);
	static int			setValueG(lua_State *l);
	static int			getStepValueG(lua_State *l);
	static int			setStepValueG(lua_State *l);
	static int			getBoundsG(lua_State *l);
	static int			setBoundsG(lua_State *l);
	static int			getStepsG(lua_State *l);
	static int			setStepsG(lua_State *l);

protected:

	enum	Flags
	{
		FLAG_DISABLED = (1 << 1),
		FLAG_IN_CALLBACK = (1 << 2)
	};

	ft::Vec2<float>		_bounds;
	float				_value;
	int					_steps;

	ACanvas::Params		_barParams;

	uint32_t			_flags;

	void				setValueWidth(int x);

private:
	SliderView(void);
	SliderView(SliderView const &src);
	SliderView			&operator=(SliderView const &rhs);
};

};

#endif
