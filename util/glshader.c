#include "glshader.h"
#include "check.h"
#include "log.h"
#include "file.h"
#include <GL/glew.h>

static void		compile_shader(u32 *id, const char *sp, u32 type);

glshader_t	glshader_create(const char *vsp, const char *fsp)
{
	glshader_t	shader = glshader_null;

	if (vsp && fsp)
		glshader_compile(&shader, vsp, fsp);
	return (shader);
}

void	glshader_compile(glshader_t *shader, const char *vsp, const char *fsp)
{
	int		success;
	char	log[512];
	u32		vs, fs;

	checkarg(shader);
	checkarg(vsp);
	checkarg(fsp);
	compile_shader(&vs, vsp, GL_VERTEX_SHADER);
	compile_shader(&fs, fsp, GL_FRAGMENT_SHADER);
	if (!(vs && fs))
		goto endoffunc;
	shader->id = glCreateProgram();
	glAttachShader(shader->id, vs);
	glAttachShader(shader->id, fs);
	glLinkProgram(shader->id);
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->id, 512, NULL, log);
		error("failed to link shader with sources:\n vertex - %s\n fragment - %s\nError Log:\n%s",
			vsp, fsp, log);
		*shader = glshader_null;
	}
endoffunc:
	if (vs)
		glDeleteShader(vs);
	if (fs)
		glDeleteShader(fs);
}

void	glshader_destroy(glshader_t *shader)
{
	checkarg(shader);
	if (shader->id)
		glDeleteProgram(shader->id);
	else
		warn("called %s() when it wasn't necessary",
			__func__);
	*shader = glshader_null;
}

void	glshader_bind(glshader_t *shader)
{
	static u32	binded_shader = 0;

	checkarg(shader);
	if (binded_shader != shader->id)
	{
		glUseProgram(shader->id);
		binded_shader = shader->id;
	}
}

bool	glshader_valid(glshader_t *shader)
{
	checkargv(shader, false);
	return (glIsProgram(shader->id));
}

static void	compile_shader(u32 *id, const char *sp, u32 type)
{
	const char	*s;
	file_t		file;
	int			success;
	char		log[512];

	file = file_create(sp);
	if (!file_valid(&file))
	{
		error("failed to load %s shader at: %s", 
			type == GL_VERTEX_SHADER ? "vertex" : "fragment",
			sp);
		*id = 0;
		return ;
	}
	s = file.content;
	*id = glCreateShader(type);
	glShaderSource(*id, 1, &s, NULL);
	glCompileShader(*id);
	file_unload(&file);
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*id, 512, NULL, log);
		error("failed to compile %s shader:\n%s",
			type == GL_VERTEX_SHADER ? "vertex" : "fragment",
			log);
		*id = 0;
	}
}
