#include "BMPLoader.h"
#include <glew.h>
#include "GLFW\glfw3.h"

unsigned char BMPLoader::bmpHeader[54];
unsigned char * BMPLoader::data;
unsigned int BMPLoader::dataPos;
unsigned int BMPLoader::width;
unsigned int BMPLoader::height;
unsigned int BMPLoader::imageSize;
unsigned int BMPLoader::textureID;
FILE * BMPLoader::file;

using namespace std;

BMPLoader::BMPLoader()
{
	file = new FILE;
}


BMPLoader::~BMPLoader()
{
	delete file;
	delete data;
}

unsigned int BMPLoader::LoadBMP(
	const char * imagepath,
	/*int & frameWidth,
	int & frameHeight,
	int & row,
	int & column,
	float & minU,
	float & maxU,
	float & minV,
	float & maxV,
	int & initialFrameID,
	float & x,
	float & y,*/
	int & spritesheetWidth,
	int & spritesheetHeight)
{
	if (fopen_s(&file, imagepath, "rb") != 0)
	{
		printf("Image could not be opened\n");
		return 0;
	}
	if (fread_s(bmpHeader,54, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}
	if (bmpHeader[0] != 'B' || bmpHeader[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(bmpHeader[0x0A]);
	imageSize = *(int*)&(bmpHeader[0x22]);
	width = *(int*)&(bmpHeader[0x12]);
	height = *(int*)&(bmpHeader[0x16]);

	// Algunos archivos BMP tienen un mal formato, as� que adivinamos la informaci�n faltante
	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataPos == 0)
	{
		dataPos = 54;
	} // El encabezado del BMP est� hecho de �sta manera

	spritesheetWidth = width;
	spritesheetHeight = height;

	// Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la informaci�n del archivo y la ponemos en el buffer
	fread_s(data,imageSize, 1, imageSize, file);

	//Todo est� en memoria ahora, as� que podemos cerrar el archivo
	fclose(file);

	// Se Crea una textura OpenGL
	glGenTextures(1, &textureID);

	// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

unsigned int BMPLoader::LoadBMP(
	const char * imagepath,
	/*int & frameWidth,
	int & frameHeight,
	int & row,
	int & column,
	float & minU,
	float & maxU,
	float & minV,
	float & maxV,
	int & initialFrameID,
	float & x,
	float & y,*/
	int & spritesheetWidth,
	int & spritesheetHeight,
	bool isTilemap)
{
	if (fopen_s(&file, imagepath, "rb") != 0)
	{
		printf("Image could not be opened\n");
		return 0;
	}
	if (fread_s(bmpHeader, 54, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}
	if (bmpHeader[0] != 'B' || bmpHeader[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(bmpHeader[0x0A]);
	imageSize = *(int*)&(bmpHeader[0x22]);
	width = *(int*)&(bmpHeader[0x12]);
	height = *(int*)&(bmpHeader[0x16]);

	// Algunos archivos BMP tienen un mal formato, as� que adivinamos la informaci�n faltante
	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataPos == 0)
	{
		dataPos = 54;
	} // El encabezado del BMP est� hecho de �sta manera

	spritesheetWidth = width;
	spritesheetHeight = height;

	// Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la informaci�n del archivo y la ponemos en el buffer
	fread_s(data, imageSize, 1, imageSize, file);

	//Todo est� en memoria ahora, as� que podemos cerrar el archivo
	fclose(file);

	GLuint textureIDaux;

	// Se Crea una textura OpenGL
	if (isTilemap)
	{
		glGenTextures(1, &textureIDaux);
		glBindTexture(GL_TEXTURE_2D, textureIDaux);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	return textureIDaux;
}
