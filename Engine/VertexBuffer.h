#pragma once

#include <glad.h>
class VertexBuffer
{
private:

	GLuint rendererID{};

public: 
	
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

