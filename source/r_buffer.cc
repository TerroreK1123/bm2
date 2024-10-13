#include "r_main.h"
#include "m_log.h"

void SBuffer::CreateBuffer()
{
	glGenBuffers(1, &this->ID);
}

void SBuffer::DestroyBuffer()
{
	glDeleteBuffers(1, &this->ID);
}

void SBuffer::Buffer(void* data, int element_size, int amount, int usage, int target,
	SVertexAttribute* attributes, int attr_amount, int vao)
{
	if (!this->ID)
	{
		M_Error("failed to buffer data! buffer is not initialized\n");
		return;
	}

	if (vao)
		glBindVertexArray(vao);
	else
		glBindVertexArray(0);

	glBindBuffer(target, this->ID);
	glBufferData(target, element_size * amount, (const void*)data, usage);
	if (attributes && attr_amount > 0 && vao)
	{
		int i = 0;
		while (i < attr_amount)
		{
			SVertexAttribute* attr = &attributes[i];
			glVertexAttribPointer(attr->index, attr->size, attr->type, attr->normalized, attr->stride, (char*)attr->offset);
			i++;
		}
	}
	glBindVertexArray(0);
	glBindBuffer(target, 0);
}