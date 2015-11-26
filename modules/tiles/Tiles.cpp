// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:58:44 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/26 17:39:12 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cmath>
#include <cfenv>
#include <cstdlib>
#include <string>
#include "tiles/Tiles.hpp"
#include "gl/gl.hpp"

static ft::Vec3<float>		c255to1(ft::Vec3<int> const c)
{
	return ft::Vec3<float>(
		static_cast<float>(c.x) / 255.f
		, static_cast<float>(c.y) / 255.f
		, static_cast<float>(c.z) / 255.f
		);
}

// * CONSTRUCTORS *********************************************************** //
// * TILES ************************** //
Tiles::Tiles() { return ; }
Tiles::~Tiles() { return ; }
Tiles::Tiles(Tiles &&src)
	: _p(src._p)
	, _vao(src._vao)
	, _vbo(src._vbo)
{
	src._p = 0;
	src._vao = 0;
    src._vbo.clear();
	return ;
}

// * TMP **************************** //
Tiles::Tmp::Tmp(ft::Vec2<int> const rectSize
				, ft::Vec2<int> const triangleSize
				, int const pointRandomRadius
	            , int const percentGray
	            , ft::Vec3<float> const gray
	            , ft::Vec3<float> const pink
	            , ft::Vec3<float> const deltaPink)
	: rectSize(rectSize)
	, triangleSize(triangleSize)
	, pointRandomRadius(pointRandomRadius)
	, percentGray(percentGray)
	, gray(gray)
	, pink(pink)
	, deltaPink(deltaPink)
{
	_buildGridDim();
	_buildGrid();
	_buildMesh();
	return ;
}

Tiles::Tmp::~Tmp() { return ; }

// * MEMBER FUNCTIONS / METHODS ********************************************* //
void				Tiles::init(ft::Vec2<int> const rectSize
								, ft::Vec2<int> const triangleSize /* = ... */
								, int const pointRandomRadius /* = ... */
								, float const percentGray /* = ... */
								, ft::Vec3<int> const gray /* = ... */
								, ft::Vec3<int> const pink /* = ... */
								, ft::Vec3<int> const deltaPink /* = ... */)
{
	Tmp			tmp(
		rectSize, triangleSize, pointRandomRadius
		, static_cast<int>(percentGray * 100.f)
		, c255to1(gray), c255to1(pink), c255to1(deltaPink));

	this->_initGlMesh(tmp);
	this->_initGlProgram();

	return ;
}

// * TMP **************************** //
void				Tiles::Tmp::_buildGridDim(void)
{
	std::fesetround(FE_UPWARD);
	gridDim.x = std::lrint(static_cast<float>(rectSize.x + pointRandomRadius * 2)
						   / triangleSize.x) + 1;
	gridDim.y = std::lrint(static_cast<float>(rectSize.y + pointRandomRadius * 2)
						   / triangleSize.y) + 1;
	return ;
}

void				Tiles::Tmp::_buildGrid(void)
{
	ft::Vec2<float>			v;
	ft::Vec2<float> const	center(static_cast<float>(rectSize.x) / 2.f,
								   static_cast<float>(rectSize.y) / 2.f);
	ft::Vec2<float> const	scale(2.f / static_cast<float>(rectSize.x),
								  2.f / static_cast<float>(rectSize.y));

	this->grid.resize(this->gridDim.y);
	for (auto &it : this->grid)
		it.resize(this->gridDim.x, point_t());
	v.y = -this->pointRandomRadius;
	for (auto &line : this->grid)
	{
		v.x = -this->pointRandomRadius;
		for (auto &point : line)
		{
			point.first = (v + _pointDeltaPos() - center) * scale;
			if (std::rand() % 100 < this->percentGray)
				point.second = gray;
			else
				point.second = pink + _pointDeltaPink();
			v.x += this->triangleSize.x;
		}
		v.y += this->triangleSize.y;
	}
	return ;
}

ft::Vec2<float>		Tiles::Tmp::_pointDeltaPos(void)
{
	float const	angle = static_cast<float>(std::rand() % 360) / 180.f * M_PI;

	return (ft::Vec2<float>(
				cos(angle) * static_cast<float>(this->pointRandomRadius)
				, sin(angle) * static_cast<float>(this->pointRandomRadius)
				));
}

ft::Vec3<float>		Tiles::Tmp::_pointDeltaPink(void)
{
	return deltaPink * (static_cast<float>(std::rand() % 1000) / 500.f - 1.f);
}

void				Tiles::Tmp::_buildMesh(void)
{
	triangle_t			tr;

	this->mesh.reserve((this->gridDim.y - 1) * (this->gridDim.x - 1) * 2);
	for (int y = 0; y < (this->gridDim.y - 1); y++)
	{
		for (int x = 0; x < (this->gridDim.x - 1); x++)
		{
			tr[0] = this->grid[y][x];
			tr[1] = this->grid[y + 1][x + 1];
			tr[2] = this->grid[y + 1][x];
			tr[0].second = tr[1].second = tr[2].second =
				(tr[0].second + tr[1].second + tr[2].second) / 3.f;
			this->mesh.push_back(tr);
			tr[0] = this->grid[y][x];
			tr[1] = this->grid[y][x + 1];
			tr[2] = this->grid[y + 1][x + 1];
			tr[0].second = tr[1].second = tr[2].second =
				(tr[0].second + tr[1].second + tr[2].second) / 3.f;
			this->mesh.push_back(tr);
		}
	}
	return ;
}
// * TILES ************************** //

static unsigned int	init_shader(unsigned int type, char const *code)
{
	unsigned int    handle;
	int             status;

	if ((handle = glCreateShader(type)) == 0)
		return (0);
	glShaderSource(handle, 1, &code, NULL);
	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		char            err_buff[512];

		glGetShaderInfoLog(handle, 512, NULL, err_buff);
		glDeleteShader(handle);
		throw std::domain_error(std::string(err_buff));
	}
	return (handle);
}

void				Tiles::_initGlProgram(void)
{
	const char *const	vert_shader_code =
		"#version 410 core\n"
		"layout (location = 0) in vec2	pos;\n"
		"layout (location = 1) in vec3	col;\n"
		"out co { vec3					col;} vs_out;"
		"void main() { vs_out.col = col;"
		"gl_Position = vec4(pos, 0.f, 1.f); }\n";
	const char *const	frag_shader_code =
		"#version 410 core\n"
		"in co { vec3					col;} fs_in;"
		"out vec4 color;\n"
		"void main() { color = vec4(fs_in.col, 1.f); }\n";
	unsigned int		vs;
	unsigned int		fs;
	int					status;

	if ((_p = glCreateProgram()) == 0)
		throw std::domain_error("Cannot create program");
	vs = init_shader(GL_VERTEX_SHADER, vert_shader_code);
	fs = init_shader(GL_FRAGMENT_SHADER, frag_shader_code);
	glAttachShader(_p, vs);
	glAttachShader(_p, fs);
	glLinkProgram(_p);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glGetProgramiv(_p, GL_LINK_STATUS, &status);
	if (status == 0)
	{
		glDeleteProgram(_p);
		throw std::domain_error("Error while linking shaders");
	}
	return ;
}

void				Tiles::_initGlMesh(Tmp const &tmp)
{
	GLuint		vbo[1];

	this->_vbo.reserve(tmp.mesh.size() * 3);
	for (auto const &it : tmp.mesh)
		for (int i = 0; i < 3; i++)
			this->_vbo.push_back(
				point_vbo_t{{it[i].first.x, it[i].first.y
							, it[i].second.x, it[i].second.y, it[i].second.z}});

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, this->_vbo.size() * sizeof(point_vbo_t)
				 , this->_vbo.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 20
						  , static_cast<char*>(0) + 8ULL);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glDeleteBuffers(1, vbo);
	return ;
}

void				Tiles::render(void) const
{
	glUseProgram(_p);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, this->_vbo.size());
	glBindVertexArray(0);
	return ;
}
