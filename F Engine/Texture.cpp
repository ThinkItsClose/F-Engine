#include "Texture.h"

// Need to move stb include and definition to here otherwise the compiler will find conflicting deinitions for the stb function definitions
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

// Default constructor
Texture::Texture(){}

Texture::Texture(std::string path, int textureType) {
	
	type = textureType;
	int width = 0;
	int height = 0;
	int channels = 0;

	// Check if file exists
	std::ifstream fileCheck(path);
	if (!fileCheck.good()) {
		std::cout << "File could not be found (" << path << ")" << std::endl;
		fileCheck.close();
	}
	fileCheck.close();

	// Initialise texture
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

	glGenTextures(1, &id);
	glBindTexture(type, id);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// This option ensures that the image data is not interpreted incorrectly by glTexImage2D when using non square textures
	// Read more here: https://stackoverflow.com/questions/58925604/glteximage2d-crashing-program
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (image) {
		// If image is RGBA or RGB load differently
		int internalFormat = 0;
		int textureFormat = 0;
		if (channels == 3) {
			textureFormat = GL_RGB;
			internalFormat = GL_COMPRESSED_RGB_ARB;
		}
		else if (channels == 4) {
			textureFormat = GL_RGBA;
			internalFormat = GL_COMPRESSED_RGBA_ARB;
		}
		else if (channels == 1) {
			textureFormat = GL_ALPHA;
			internalFormat = GL_COMPRESSED_ALPHA_ARB;
		}

		if (textureFormat == 0) {
			std::cout << "Texture loading failed for: " << path << " (An invalid amount of channels was found: " << channels << ")" << std::endl;
		} else {
			// Thank the lord above for 
			// https://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf

			std::cout << "" << std::endl;
			glTexImage2D(type, 0, internalFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);

			// If image is compressed we can save it to the disk so it can be streamed in faster and pre converted
			// This is the optimal solution for production projects as it saves on disk space, memory and cpu time
			// When not in production however, it may be worth it to convert the textures on the fly as having copies of large textures
			// may take up alot of hard drive space over time
			// Note: there may be an issue with cross platform applications when using this method
			int compressed;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_ARB, &compressed);

			if (compressed) {
				// todo: Could save to file here to improve texture streaming/storing in the future
				// refer to url for theory
			} else {
				std::cout << "Texture compression failed for: " << path << std::endl;
			}
		}
	}
	else {
		std::cout << "Texture loading failed for: " << path << std::endl;
	}

	// Unbind all textures
	stbi_image_free(image);
}

unsigned int Texture::GetID() {
	return id;
}

int Texture::GetType() {
	return type;
}