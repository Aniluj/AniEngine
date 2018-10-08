#include "BMPLoader.h"

unsigned char BMPLoader::bmpHeader[54];
unsigned char * BMPLoader::data;
unsigned int BMPLoader::dataPos;
unsigned int BMPLoader::width;
unsigned int BMPLoader::height;
unsigned int BMPLoader::imageSize;
FILE * BMPLoader::file;

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

	  // Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la informaci�n del archivo y la ponemos en el buffer
	fread_s(data,imageSize, 1, imageSize, file);

	//Todo est� en memoria ahora, as� que podemos cerrar el archivo
	fclose(file);
}