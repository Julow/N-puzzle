// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   gl.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/07 22:46:21 by juloo             #+#    #+#             //
//   Updated: 2015/10/07 22:46:55 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GL_HPP
# define GL_HPP

extern "C"
{

#ifdef MAC_OS_MODE
# define GLFW_INCLUDE_GLCOREARB
#else
# include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

}

#endif
