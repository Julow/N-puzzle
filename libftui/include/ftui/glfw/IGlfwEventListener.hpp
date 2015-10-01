/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGlfwEventListener.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 13:22:26 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/01 14:42:03 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGLFWEVENTLISTENER_HPP
# define IGLFWEVENTLISTENER_HPP

namespace ftui
{

class	IGlfwEventListener
{
public:
	virtual ~IGlfwEventListener(void){}

	virtual void	onKeyUp(int key, int scancode, int mods) = 0;
	virtual void	onKeyDown(int key, int scancode, int mods) = 0;
	virtual void	onKeyRepeat(int key, int scancode, int mods) = 0;

	virtual void	onMouseEnter(void) = 0;
	virtual void	onMouseLeave(void) = 0;

	virtual void	onMouseMove(double x, double y) = 0;
	virtual void	onMouseScroll(double x, double y) = 0;

	virtual void	onMouseUp(int button, int mods) = 0;
	virtual void	onMouseDown(int button, int mods) = 0;

protected:

private:
};

};

#endif
