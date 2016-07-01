#undef UNICODE
#include "Texture.h"
#include "glerr.h"
Texture::Texture(const char * plik)
{
	LoadGLTextures(plik);
};

Texture::Texture()
{
	GLDEBUG(glGenTextures(1, &nazwa);)

};

Texture::~Texture(void)
{
	GLDEBUG(glDeleteTextures(1, &nazwa);)
};

int Texture::LoadGLTextures(const char * plik)
{

	// Status: TRUE, jesli wszystko OK
	Status = FALSE;
	// Struktura obrazka

	GLDEBUG(glGenTextures(1, &nazwa);)

		//glEnable(GL_TEXTURE_2D);
		AUX_RGBImageRec *TextureImage;
	// Na wszelki wypadek zerujemy pamiec tekstury
	//	memset(TextureImage, 0, sizeof(void*)*1);		
	// Wczytanie tekstury, sprawdzenie, czy wystapily bledy

	GLDEBUG(glBindTexture(GL_TEXTURE_2D, nazwa);)

		GLDEBUG(glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);)

		if (TextureImage = LoadBMP(plik))
		{
			Status = TRUE;

			//float fLArgest;
			//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
			GLDEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);)
				GLDEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)
				GLDEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)
				GLDEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);)
				//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
				GLDEBUG(gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data); )



		}

	// Sprawdzamy, czy struktura obrazka istnieje, zeby zwolnic zajmowana pamiec
	if (TextureImage)
	{
		// Jesli tak, to sprawdzamy, czy obraz tekstury istnieje
		if (TextureImage->data)
			// Skoro tak, to zwalniamy go
			free(TextureImage->data);
		// Skoro tak, to zwalniamy strukture obrazka
		free(TextureImage);
	}
	// Zwracamy informacje o tym, czy sie udalo
	return Status;


};
AUX_RGBImageRec* Texture::LoadBMP(const char *Filename)
{
	FILE *File = NULL;

	// Jeœli u¿ytkownik nie poda³ nazwy pliku, zwracamy NULL
	if (!Filename)
		return NULL;
	// Sprawdzamy, czy plik istnieje
	//fopen_s(&File,Filename, "r");		
	File = fopen(Filename, "r");
	if (File)
	{
		fclose(File);
		// Skoro istnieje, to mozna wywolac funkcje wczytujaca
		return auxDIBImageLoad(Filename);
	}
	return NULL;
};

GLuint Texture::getName()
{
	return nazwa;
};
void Texture::Bind()
{
	GLDEBUG(glBindTexture(GL_TEXTURE_2D, nazwa);)
}