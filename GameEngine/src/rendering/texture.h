#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>
#include <FREEIMAGE\FreeImage.h>
#include <string>

class Texture
{
public:
	Texture(){};
	Texture(const std::string& filename, GLenum target = GL_TEXTURE_2D , int magFilter = 3, int minFilter = 8, bool genMipMaps = true);
	Texture::Texture(int width, int height, BYTE* data, GLenum target = GL_TEXTURE_2D, int magFilter = 3, int minFilter = 8, bool genMipMaps = true);

	void Texture::SetSamplerParameter(GLenum parameter, GLenum value); //Specify a custon random parameter
	void Texture::Bind(GLenum textureUnit);
	void Texture::ReleaseTexture();
private:
	int m_width;
	int m_height;
	int m_bitesPerPixel;
	bool m_mipmaps;
	
	GLenum m_target;
	GLuint m_textureId;

	GLuint m_samplerId; 
	int m_magFilter;
	int m_minFilter;

	bool m_freeTexture;

	bool LoadTexture(const std::string& filename);
	void InitTexture(int width, int height, BYTE* bitDataPointer, GLenum target);
	void SetFiltering();
};

enum TextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR = 1, // Bilinear criterion for magnification
	TEXTURE_FILTER_MAG_NEAREST_MIPMAP = 2, // Nearest criterion for magnification, but on closest mipmap
	TEXTURE_FILTER_MAG_BILINEAR_MIPMAP = 3, // Bilinear criterion for magnification, but on closest mipmap
	TEXTURE_FILTER_MAG_TRILINEAR = 4, // Bilinear criterion for magnification on two closest mipmaps, then averaged
	TEXTURE_FILTER_MIN_NEAREST = 5, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR = 6, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP = 7, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP = 8, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR = 9, // Bilinear criterion for minification on two closest mipmaps, then averaged
};
#endif 