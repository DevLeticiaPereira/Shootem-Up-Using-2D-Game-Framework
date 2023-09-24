#pragma once

#include <glad.h>
class IndexBuffer
{
private:

	GLuint rendererID{};
	GLuint count{};

public: 
	
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return count; };
};

