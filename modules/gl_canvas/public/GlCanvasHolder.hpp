// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GlCanvasHolder.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/07 20:31:56 by juloo             #+#    #+#             //
//   Updated: 2015/11/24 12:17:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GLCANVASHOLDER_HPP
# define GLCANVASHOLDER_HPP

# include "ftui/ACanvas.hpp"
# include "GlCanvas.hpp"

namespace gl
{

/*
** Hold and render a 2d canvas (ftui::Canvas)
*/
class	GlCanvasHolder
{
public:
	GlCanvasHolder(int width, int height);
	virtual ~GlCanvasHolder(void);

	/*
	** Init
	** throw an exception if called twice
	** need to be called before any call to getCanvas() or render()
	*/
	void				init(void);

	/*
	** Return a canvas that can be used to draw in
	*/
	ftui::ACanvas		&getCanvas(void);

	/*
	** Render the current canvas
	*/
	void				render(void);

protected:
	GlCanvas			_canvas;
	int					_width;
	int					_height;

	unsigned int		_shaders;
	unsigned int		_quad;
	unsigned int		_texture;

	void				init_shaders(void);
	void				init_quad(void);
	void				init_texture(void);

private:
	GlCanvasHolder(void);
	GlCanvasHolder(GlCanvasHolder const &src);
	GlCanvasHolder		&operator=(GlCanvasHolder const &rhs);
};

};

#endif
