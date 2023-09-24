#pragma once
#include <glad.h>
#include <iostream>
#include <map>

#include "Transform.h"
#include "Texture.h"
#include "glm.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
	public:

		Renderer();

		static Renderer* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new Renderer(); }

		void Init();
		void Draw(Transform* transform, Texture* texture, float angle , float col = 1, float lines = 1, float totalColunm = 1, float totalLines = 1, bool flip = false, float r = 0, float g = 0, float b = 0, float alpha = 0);
		void Clear() const;

	private:

		static Renderer* sInstance;
		glm::mat4 proj, view, mvp, translationMatrix, rotationMatrixZ;
};