#include "Texture.h"
#include "stb_image/stb_image.h"

// THIS WHOLE ALGORITHM COULD BE REPLACED WITH SOMETHING THAT GENERATES IMAGES PER-PIXEL RATHER THAN 
// THE SHADER

Texture::Texture(const std::string& path)
	: m_Id(0), m_Filepath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	// c_str() converts to a C style string (char* strName)
	// width, height, and BPP are sent by reference here because their memory address already exists here in the 
		// texture object. the function they are used in will actually set the values for these variables based on 
		// the texture that is read in. 
		// the 4 means 4 channels AKA R, G, B, A 
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);

	// Look into this function
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Here this pixel data could be saved in order to manipulate the raw pixel data and reassign the values
	if (m_LocalBuffer){
		stbi_image_free(m_LocalBuffer);
		// Manipulate pixel DATA!!!
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::BindUnit(unsigned int slot) const
{
	//glBindTextureUnit(slot, m_Id);
	glBindTexture(slot, m_Id);
}

void Texture::Unbind() const
{
}
