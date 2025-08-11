#include "glbuffer.h"
#include "check.h"
#include "log.h"
#include <GL/glew.h>

static const u32	buffer_target[_GLBUFFERTYPE_COUNT] = {
	0,							// INVALID
	GL_ARRAY_BUFFER,			// ARRAY
	GL_ELEMENT_ARRAY_BUFFER,	// ELEMENT
	0,							// VERTEX ARRAY
};

#define checkbuffertype(bufferptr)						\
	do {												\
		glbuffer_t *buf = (bufferptr);					\
		if (!(buf->type > GLBUFFER_INVALID				\
			&& buf->type < _GLBUFFERTYPE_COUNT))		\
		{												\
			error("Calling %s() but given buffer is "	\
				"invalid", __func__);					\
			return ;									\
		}												\
	} while (0)

#define checkbuffer(bufferptr)	\
	checkarg(bufferptr);		\
	checkbuffertype(bufferptr)	

glbuffer_t	glbuffer_create(glbuffertype_t type)
{
	glbuffer_t	buffer = {
		.size = 0,
		.id = 0,
		.type = GLBUFFER_INVALID,
	};

	if (type >= _GLBUFFERTYPE_COUNT || type == GLBUFFER_INVALID)
	{
		error("given type is invalid: %d", type);
		return (glbuffer_null);
	}
	switch (type)
	{
		case (GLBUFFER_ARRAY):
		case (GLBUFFER_ELEMENT):
			glGenBuffers(1, &buffer.id);
			break ;
		case (GLBUFFER_VERTEX_ARRAY):
			glGenVertexArrays(1, &buffer.id);
			break ;
		default:
			error("given type isn't defined: %d", type);
			return (glbuffer_null);
	}
	buffer.type = type;
	glbuffer_bind(&buffer);
	return (buffer);
}

void		glbuffer_bind(glbuffer_t *buffer)
{
	static u32	binded_buffers[_GLBUFFERTYPE_COUNT];

	checkbuffer(buffer);
	if (buffer->id != binded_buffers[buffer->type])
	{
		switch (buffer->type)
		{
			case (GLBUFFER_ARRAY):
			case (GLBUFFER_ELEMENT):
				glBindBuffer(buffer_target[buffer->type], buffer->id);
				break ;
			case (GLBUFFER_VERTEX_ARRAY):
				glBindVertexArray(buffer->id);
				break ;
			default:
				error("shouldn't happen");
				break ;
		}
	}
	binded_buffers[buffer->type] = buffer->id;
}

void		glbuffer_data(glbuffer_t *buffer, u64 datasize, 
	void *data, u32 glusage)
{
	checkbuffer(buffer);
	glbuffer_bind(buffer);
	glBufferData(buffer_target[buffer->type], datasize, data, glusage);
	buffer->size = datasize;
}

void		glbuffer_subdata(glbuffer_t *buffer, u64 offset, 
	u64 datasize, void *data)
{
	checkbuffer(buffer);
	if (offset + datasize > buffer->size)
	{
		warn("buffer overflow for buffer %d (type: %d)",
			buffer->id, buffer->type);
		return ;
	}
	glbuffer_bind(buffer);
	glBufferSubData(buffer_target[buffer->type], offset, datasize, data);
}

void		glbuffer_destroy(glbuffer_t *buffer)
{
	checkbuffer(buffer);
	if (buffer->id)
	{
		switch (buffer->type)
		{
			case (GLBUFFER_ARRAY):
			case (GLBUFFER_ELEMENT):
				glDeleteBuffers(1, &buffer->id);
				break ;
			case (GLBUFFER_VERTEX_ARRAY):
				glDeleteVertexArrays(1, &buffer->id);
				break ;
			default:
				error("shouldn't happen");
				break ;
		}
	}
	else
		warn("called %s() when it wasn't necessary",
			__func__);
	*buffer = glbuffer_null;
}

bool		glbuffer_valid(glbuffer_t *buffer)
{
	checkargv(buffer, false);
	if (!(buffer->type > GLBUFFER_INVALID 
		&& buffer->type < _GLBUFFERTYPE_COUNT)
		|| !buffer->id)
		return false;
	switch (buffer->type)
	{
		case (GLBUFFER_ARRAY):
		case (GLBUFFER_ELEMENT):
			return glIsBuffer(buffer->id);
		case (GLBUFFER_VERTEX_ARRAY):
			return glIsVertexArray(buffer->id);
		default:
			error("given type isn't defined: %d", buffer->type);
			return false;
	}
}
