#include "Texture.h"

// Need to move stb include and definition to here otherwise the compiler will find conflicting deinitions for the stb function definitions
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

// Default constructor
Texture::Texture(){}

Texture::Texture(std::string path, int textureType) {
	
	type = textureType;
	int width;
	int height;
	int channels;

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

	// This option ensures that the image data is not interpreted incorrectly by glTexImage2D when using non square textures
	// Read more here: https://stackoverflow.com/questions/58925604/glteximage2d-crashing-program
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (image) {
		// If image is RGBA or RGB load differently
		int format = 0;
		if (channels == 3) {
			format = GL_RGB;
		}
		else if (channels == 4) {
			format = GL_RGBA;
		}
		else if (channels == 1) {
			format = GL_ALPHA;
		}

		if (format == 0) {
			std::cout << "Texture loading failed for: " << path << " (An invalid amount of channels was found: " << channels << ")" << std::endl;
		} else {
			glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type);

			glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	}
	else {
		std::cout << "Texture loading failed for: " << path << std::endl;
	}

	// Unbind all textures
	glActiveTexture(0);
	glBindTexture(type, 0);
	stbi_image_free(image);
}

unsigned int Texture::GetID() {
	return id;
}

int Texture::GetType() {
	return type;
}