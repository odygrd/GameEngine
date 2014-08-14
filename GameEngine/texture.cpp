#include <FREEIMAGE\FreeImage.h>
#include "texture.h"

using namespace std;

Texture* Texture::m_lastBinded = NULL;

Texture::Texture(const string& filename, GLenum target, int magFilter, int minFilter, bool genMipmaps)
{
	m_target = target;
	m_magFilter = magFilter;
	m_minFilter = minFilter;
	m_mipmaps = genMipmaps;

	if (LoadTexture(filename))
	{
		SetFiltering();
	}
}

Texture::~Texture()
{
}

bool Texture::LoadTexture(const string& filename)
{
	FREE_IMAGE_FORMAT imageformat = FIF_UNKNOWN;
	FIBITMAP* m_bitmap(0);

	imageformat = FreeImage_GetFileType(filename.c_str(), 0); // Check the file signature and deduce its format

	if (imageformat == FIF_UNKNOWN) // If still unknown, try to guess the file format from the file extension
		imageformat = FreeImage_GetFIFFromFilename(filename.c_str());

	if (imageformat == FIF_UNKNOWN) // If still unkown, return failure
	{
		printf("Error: Unknown texture format for file %s\n", filename);
		m_textureId = 0;
		return false;
	}

	if (FreeImage_FIFSupportsReading(imageformat)) // Check if the plugin has reading capabilities and load the file
		m_bitmap = FreeImage_Load(imageformat, filename.c_str());
	if (!m_bitmap)
	{
		printf("Error: Loading the texture file %s\n", filename);
		m_textureId = 0;
		return false;
	}

	BYTE* bitDataPointer = FreeImage_GetBits(m_bitmap); // Retrieve the image data

	m_width = FreeImage_GetWidth(m_bitmap); // Get the image width and height
	m_height = FreeImage_GetHeight(m_bitmap);
	m_bitesPerPixel = FreeImage_GetBPP(m_bitmap);

	if (bitDataPointer == NULL || m_width == 0 || m_height == 0) // If somehow one of these failed (they shouldn't), return failure
	{
		printf("Error: Freeimage data pointer/width/height for texture %s is null\n", filename);
		m_textureId = 0;
		return false;
	}

	InitTexture(m_width, m_height, bitDataPointer, m_target);

	FreeImage_Unload(m_bitmap);

	return true;
}

void Texture::InitTexture(int width, int height, BYTE* bitDataPointer, GLenum target)
{
	m_freeTexture = true;
	int iFormat = m_bitesPerPixel == 24 ? GL_BGR : m_bitesPerPixel == 8 ? GL_LUMINANCE : 0;

	glGenTextures(1, &m_textureId);
	glBindTexture(target, m_textureId);
	glTexImage2D(target, 0, GL_RGB, m_width, m_height, 0, iFormat, GL_UNSIGNED_BYTE, bitDataPointer);
}

void Texture::SetFiltering()
{
	if (m_mipmaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glGenSamplers(1, &m_samplerId);

	// Set magnification filter
	if (m_magFilter == TEXTURE_FILTER_MAG_NEAREST)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else if (m_magFilter == TEXTURE_FILTER_MAG_BILINEAR)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	else if (m_minFilter == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	else if (m_minFilter == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	else if (m_minFilter == TEXTURE_FILTER_MIN_TRILINEAR)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Set minification filter
	if (m_minFilter == TEXTURE_FILTER_MIN_NEAREST)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	else if (m_minFilter == TEXTURE_FILTER_MIN_BILINEAR)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	else if (m_minFilter == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	else if (m_minFilter == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	else if (m_minFilter == TEXTURE_FILTER_MIN_TRILINEAR)
		glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::SetSamplerParameter(GLenum parameter, GLenum value)
{
	glSamplerParameteri(m_samplerId, parameter, value);
}

void Texture::Bind(GLenum textureUnit)
{
	if (m_lastBinded != this)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(m_target, m_textureId);
		glBindSampler(textureUnit, m_samplerId);
	}
}

void Texture::ReleaseTexture()
{
	glDeleteSamplers(1, &m_samplerId);
	glDeleteTextures(1, &m_textureId);
}
