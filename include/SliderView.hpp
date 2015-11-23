// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SliderView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:27:39 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/23 17:47:51 by jaguillo         ###   ########.fr       //
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
** TODO: lua c functions
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

	float				getValue(void) const;
	void				setValue(float val);

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
	** 	getValue() return the old value
	*/
	virtual void		onValueChange(float val);

	virtual void		onDraw(ftui::Canvas &canvas);

	virtual bool		onMouseDown(int x, int y, int button, int mods);
	virtual bool		onMouseUp(int x, int y, int button, int mods);
	virtual bool		onMouseMove(int x, int y);
	virtual bool		onMouseScroll(int x, int y, float delta);

	virtual void		onAttach(void);
	virtual void		onDetach(void);

protected:

	ft::Vec2<float>		_bounds;
	float				_value;

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
