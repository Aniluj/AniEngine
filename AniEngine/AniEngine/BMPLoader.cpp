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

unsigned int BMPLoader::LoadBMP(const char * imagepath)
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

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataPos == 0)
	{
		dataPos = 54;
	} // El encabezado del BMP está hecho de ésta manera

	// Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la información del archivo y la ponemos en el buffer
	fread_s(data, imageSize, 1, imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
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

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataPos == 0)
	{
		dataPos = 54;
	} // El encabezado del BMP está hecho de ésta manera

	//cout << "W: " << width << endl;
	//cout << "H: " << height << endl;

	spritesheetWidth = width;
	spritesheetHeight = height;

	/*
	x = (float)(initialFrameID % column) * (float)frameWidth;
	y = ((float)initialFrameID / (float)row) * (float)frameHeight;

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	maxU = (x + frameWidth) / width; cout << "maxU: " << maxU << endl;
	minU = x / width; cout << "minU: " << minU << endl;
	minV = 1.0f - ((y + frameHeight) / height); cout << "minV: " << minV << endl;
	maxV = 1.0f - (y / height); cout << "maxV: " << maxV << endl;
	*/

	// Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la información del archivo y la ponemos en el buffer
	fread_s(data,imageSize, 1, imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
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
