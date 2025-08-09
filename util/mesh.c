#include "mesh.h"
#include "check.h"
#include "log.h"
#include <GL/glew.h>

#define checkmeshtype(meshptr)						\
	do {											\
		mesh_t	*m = (meshptr);						\
		if (!(m->type > MESH_INVALID				\
			&& m->type < _MESHTYPE_COUNT))			\
		{											\
			error("Calling %s() but given mesh is "	\
				"invalid", __func__);				\
			return ;								\
		}											\
	} while (0)

#define checkmesh(meshptr)	\
	checkarg(meshptr);		\
	checkmeshtype(meshptr)

mesh_t	mesh_create(meshtype_t type)
{
	mesh_t	mesh = mesh_null;
	int		expectedbuffer;

	if (type >= _MESHTYPE_COUNT || type == MESH_INVALID)
	{
		error("given type is invalid: %d", type);
		return (mesh_null);
	}
	switch (type)
	{
		case (MESH_INSTANCED_ELEMENT):
			mesh.vao = glbuffer_create(GLBUFFER_VERTEX_ARRAY);
			mesh.vbo = glbuffer_create(GLBUFFER_ARRAY);
			mesh.ebo = glbuffer_create(GLBUFFER_ELEMENT);
			mesh.ibo = glbuffer_create(GLBUFFER_ARRAY);
			expectedbuffer = 4;
			break ;
		default:
			error("Mesh type isn't defined: %d", type);
			return (mesh_null);
	}
	mesh.type = type;
	for (int i = 0; i < _MESHSBUFFERCOUNT; i++)
		if (glbuffer_valid(&mesh.buffers[i]))
			expectedbuffer--;
	if (expectedbuffer != 0)
	{
		error("something went wrong when creating mesh");
		mesh_destroy(&mesh);
		return (mesh_null);
	}
	return (mesh);
}

void	mesh_setup(mesh_t *mesh, meshsetup_t desc)
{
	meshattributes_t	*tmp;
	int					validbuffer = 0;
	int					attribcount = 0;

	checkmesh(mesh);
	for (int i = 0; i < _MESHSBUFFERCOUNT; i++)
		if (glbuffer_valid(&mesh->buffers[i]))
			validbuffer++;
	glbuffer_bind(&mesh->vao);
	switch (mesh->type)
	{
		case (MESH_INSTANCED_ELEMENT):
			if (validbuffer != 4)
			{
				error("Trying to setup invalid mesh");
				break ;
			}
			glbuffer_data(&mesh->vbo, 
				desc.vertices.unitsize * desc.vertices.count,
				desc.vertices.data,
				desc.vertices.usage);
			tmp = desc.vertices.attributes;
			for (u32 i = 0; i < desc.vertices.attributes_count; i++)
			{
				glEnableVertexAttribArray(attribcount);
				glVertexAttribPointer(attribcount,
					tmp[i].size,
					tmp[i].gltype,
					tmp[i].normalized,
					desc.vertices.unitsize,
					(void*)tmp[i].offset);
				attribcount++;
			}
			glbuffer_data(&mesh->ebo,
				desc.elements.totlsize,
				desc.elements.data,
				desc.elements.usage);
			mesh->ecount = desc.elements.count;
			mesh->gletype = desc.elements.gltype;
			glbuffer_data(&mesh->ibo,
				desc.instances.capacity * desc.instances.unitsize,
				NULL,
				desc.instances.usage);
			mesh->isize = desc.instances.unitsize;
			mesh->icap = desc.instances.capacity;
			tmp = desc.instances.attributes;
			for (u32 i = 0; i < desc.instances.attributes_count; i++)
			{
				glEnableVertexAttribArray(attribcount);
				glVertexAttribPointer(attribcount,
					tmp[i].size,
					tmp[i].gltype,
					tmp[i].normalized,
					desc.instances.unitsize,
					(void*)tmp[i].offset);
				glVertexAttribDivisor(attribcount, 1);
				attribcount++;
			}
			break ;
		default:
			error("shouldn't happen");
			break ;
	}
}

void	mesh_draw(mesh_t *mesh, u64 offset, u32 glmode)
{
	checkmesh(mesh);
	if (mesh->icount < 1)
	{
		warn("trying to draw instanced mesh with no instances");
		return ;
	}
	glbuffer_bind(&mesh->vao);
	switch (mesh->type)
	{
		case (MESH_INSTANCED_ELEMENT):
			glDrawElementsInstanced(
				glmode, 
				mesh->ecount, 
				mesh->gletype,
				(void*)offset, 
				mesh->icount);
			break ;
		default:
			error("not supposed to happen");
			break ;
	}
}

void	mesh_append(mesh_t *mesh, u32 icount, void *instances)
{
	checkmesh(mesh);
	if (mesh->type != MESH_INSTANCED_ELEMENT)
	{
		warn("trying append instances to a non instanced mesh");
		return ;
	}
	if (icount == 0)
	{
		warn("adding 0 instances to mesh");
		return ;
	}
	if (mesh->icap < mesh->icount + icount)
	{
		warn("instances buffer overflow");
		return ;
	}
	glbuffer_subdata(&mesh->ibo, 
		mesh->icount, 
		icount * mesh->isize, 
		instances);
	mesh->icount += icount;
}

void	mesh_destroy(mesh_t *mesh)
{
	int	destroyed_buffer = 0;

	checkmesh(mesh);
	for (int i = 0; i < _MESHSBUFFERCOUNT; i++)
	{
		if (glbuffer_valid(&mesh->buffers[i]))
		{
			glbuffer_destroy(&mesh->buffers[i]);
			destroyed_buffer++;
		}
	}
	if (!destroyed_buffer)
		warn("called %s() when it wasn't necessary",
			__func__);
	*mesh = (mesh_t){0};
}

bool	mesh_valid(mesh_t *mesh)
{
	int	expectedbuffer;

	checkargv(mesh, false);
	if (!(mesh->type > MESH_INVALID
		&& mesh->type < _MESHTYPE_COUNT))
		return false;
	switch (mesh->type)
	{
		case (MESH_INSTANCED_ELEMENT):
			expectedbuffer = 4;
			break ;
		default:
			error("Shouldn't happen");
			break ;
	}
	for (int i = 0; i < _MESHSBUFFERCOUNT; i++)
		if (glbuffer_valid(&mesh->buffers[i]))
			expectedbuffer--;
	if (expectedbuffer != 0)
		return false;
	return true;
}

void	mesh_clear(mesh_t *mesh)
{
	checkmesh(mesh);
	mesh->icount = 0;
}
