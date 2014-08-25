#ifndef MATERIAL_H
#define MATERIAL_H
#include "texture.h"
#include "../core/common.h"

class Material
{
public:
	Material(Texture* texture = NULL, const vec3& color = vec3(1, 1, 1)) : m_texture(texture), m_color(color){}
	~Material();

	inline Texture* GetTexture(){ return m_texture; }
	inline const vec3& GetColor(){ return m_color; }
private:
	Texture* m_texture;
	vec3 m_color;
};

#endif