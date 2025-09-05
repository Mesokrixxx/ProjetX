#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "string.h"
#include "file.h"

bool	check_sp(const char *sp, const char *suffix);
bool	shader_compile(u32 *sid, char **ss, u32 gl_stype);
void	shader_load(shader_t *s);

void	shader_create(shader_t *s, const char *vsp, const char *fsp)
{
	bool	vs, fs;

	*s = (shader_t){0};
	if (!check_sp(vsp, ".vert"))
	{
		fprintf(stderr, "vertex source path must point "
			"to a '.vert' terminated file\n");
		return ;
	}
	if (!check_sp(fsp, ".frag"))
	{
		fprintf(stderr, "fragment source path must point "
			"to a '.frag' terminated file\n");
		return ;
	}
	vs = file_exists(fsp);
	if (!vs)
	{
		fprintf(stderr, "vertex shader file %s does not exists.\n", 
			vsp);
		return ;
	}
	fs = file_exists(vsp);
	if (!fs)
	{
		fprintf(stderr, "fragment shader file %s does not exists.\n", 
			vsp);
		return ;
	}
	s->vsp = px_strdup(vsp);
	s->fsp = px_strdup(fsp);
	shader_load(s);
}

void	shader_bind(shader_t *s)
{
	static u32	sbinded;

	if (sbinded != s->id)
	{
		sbinded = s->id;
		glUseProgram(s->id);
	}
}

void	shader_reload(shader_t *s)
{
	if (!s)
		return ;
	glDeleteShader(s->id);
	shader_load(s);	
}

void	shader_destroy(shader_t *s)
{
	free(s->vsp);
	free(s->fsp);
	glDeleteProgram(s->id);
	*s = (shader_t){0};
}

bool	check_sp(const char *sp, const char *suffix)
{
	u64	splen;
	u64	suffixlen;

	if (!sp)
		return false;
	splen = px_strlen(sp);
	if (!splen)
		return false;
	suffixlen = px_strlen(suffix);
	if (suffixlen > splen)
		return false;
	return px_strcmp(sp + splen - suffixlen, suffix);
}

bool	shader_compile(u32 *sid, char **ss, u32 gl_stype)
{
	char	infoLog[512];
	int		success;

	*sid = glCreateShader(gl_stype);
	glShaderSource(*sid, 1, (const char **)ss, NULL);
	glCompileShader(*sid);
	glGetShaderiv(*sid, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*sid, 512, NULL, infoLog);
		fprintf(stderr, "Error when compiling %s shader:\n%s\n>>> %s",
			gl_stype == GL_VERTEX_SHADER ? "vertex" : "fragment", 
			*ss, infoLog);
		return false;
	}
	return true;
}

void	shader_load(shader_t *s)
{
	char	*vs, *fs;
	u32		vid = 0;
	u32		fid = 0;
	bool	compiled;
	int		success;
	char	infoLog[512];

	vs = file_read(s->vsp);
	fs = file_read(s->fsp);
	compiled = 
		shader_compile(&vid, &vs, GL_VERTEX_SHADER) 
		&& shader_compile(&fid, &fs, GL_FRAGMENT_SHADER);
	if (!compiled)
		goto skipProgramCreation;
	s->id = glCreateProgram();
	glAttachShader(s->id, vid);
	glAttachShader(s->id, fid);
	glLinkProgram(s->id);
	glGetProgramiv(s->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(s->id, 512, NULL, infoLog);
		fprintf(stderr, "Fail to relink shader with given paths:\n> %s\n> %s\n",
			s->vsp, s->fsp);
		glDeleteProgram(s->id);
		s->id = 0;
	}
skipProgramCreation:
	glDeleteShader(vid);
	glDeleteShader(fid);
	free(vs);
	free(fs);
}
