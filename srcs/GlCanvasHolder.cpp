// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GlCanvasHolder.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/07 21:38:50 by juloo             #+#    #+#             //
//   Updated: 2015/10/07 23:00:07 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GlCanvasHolder.hpp"
#include "gl.hpp"
#include "ft/utils.hpp"

#include <stdexcept>

GlCanvasHolder::GlCanvasHolder(int width, int height) :
	_bitmap(NULL),
	_width(width),
	_height(height),
	_shaders(0),
	_quad(0)
{
}

GlCanvasHolder::~GlCanvasHolder(void)
{
}

void			GlCanvasHolder::init(void)
{
	if (_bitmap != NULL)
		throw std::domain_error("init() called twice");
	_bitmap = new ftui::Canvas::color_t[_width * _height];
	init_shaders();
	init_quad();
	init_texture();
}

ftui::Canvas	GlCanvasHolder::getCanvas(void)
{
	if (_bitmap == NULL)
		throw std::domain_error("getCanvas() call before init()");
	return (ftui::Canvas(_bitmap, _width, _height));
}

void			GlCanvasHolder::render(void)
{
	if (_bitmap == NULL)
		throw std::domain_error("render() call before init()");
	glUseProgram(_shaders);
	glBindVertexArray(_quad);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glDrawArrays(GL_QUADS, 0, 4),
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

/*
** ========================================================================== **
** init texture
*/

void			GlCanvasHolder::init_texture(void)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, _bitmap);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*
** ========================================================================== **
** init quad
*/

void			GlCanvasHolder::init_quad(void)
{
	static float const	vertices[] = {
		-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f
	};
	unsigned int	vbo;

	glGenVertexArrays(1, &_quad);
	glBindVertexArray(_quad);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
}

/*
** ========================================================================== **
** init shaders
*/

static unsigned int	init_shader(unsigned int type, char const *code)
{
	unsigned int	handle;
	int				status;

	if ((handle = glCreateShader(type)) == 0)
		return (0);
	glShaderSource(handle, 1, &code, NULL);
	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		char			err_buff[512];

		glGetShaderInfoLog(handle, 512, NULL, err_buff);
		glDeleteShader(handle);
		throw std::domain_error(std::string(err_buff));
	}
	return (handle);
}

void			GlCanvasHolder::init_shaders(void)
{
	static const char *const	vert_shader_code =
		"#version 410 core\n"
		"layout (location = 0) in vec2	buff_tex;\n"
		"void main() { }\n";
	static const char *const	frag_shader_code =
		"#version 410 core\n"
		"uniform sampler2D bitmap;\n"
		"out vec4 color;\n"
		"void main() { color = texture(bitmap, gl_PointCoord); }\n";
	unsigned int	vert;
	unsigned int	frag;
	int				status;

	if ((_shaders = glCreateProgram()) == 0)
		throw std::domain_error("Cannot create program");
	vert = init_shader(GL_VERTEX_SHADER, vert_shader_code);
	frag = init_shader(GL_FRAGMENT_SHADER, frag_shader_code);
	glAttachShader(_shaders, vert);
	glAttachShader(_shaders, frag);
	glLinkProgram(_shaders);
	glDeleteShader(vert);
	glDeleteShader(frag);
	glGetProgramiv(_shaders, GL_LINK_STATUS, &status);
	if (status == 0)
	{
		glDeleteProgram(_shaders);
		throw std::domain_error("Error while linking shaders");
	}
}
