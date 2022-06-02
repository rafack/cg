/******************************************************************************\
* Virtual Cow Parade -- Texture Generator                                      *
*                                                                              *
* T�cnicas Avan�adas de Computa��o Gr�fica 2010-2                              *
*                                                                              *
* Este programa utiliza a libnoise (http://libnoise.sourceforge.net) para a    *
* gera��o de texturas procedurais                                              *
*                                                                              *
*                                                                              *
* Projeto iniciado por Rossana Queiroz  em 08/11/2010                          *
*                                                                              *
\******************************************************************************/

#include <iostream>
#include <noise/noise.h>
#include "noiseutils.h"

#include <sstream>


using namespace noise;


utils::NoiseMap BuildAHeightMap (int w, int h, float *bounds) {
	//Classe para a cria��o de ru�do de perlin (Perlin Noise)
	module::Perlin myModule;

	//Utilizando a biblioteca auxiliar noiseutils, podemos instanciar um mapa de noise, que neste caso ser� utilizado para gerar um heightmap
	utils::NoiseMap heightMap;

	//
   utils::NoiseMapBuilderPlane heightMapBuilder;
   heightMapBuilder.SetSourceModule (myModule);
   heightMapBuilder.SetDestNoiseMap (heightMap);
   heightMapBuilder.SetDestSize (w, h);
   heightMapBuilder.SetBounds (bounds[0], bounds[1], bounds[2], bounds[3]);
   heightMapBuilder.Build ();

   return heightMap;
}

utils::NoiseMap BuildASphericalHeightMap(int w, int h, float* bounds) {
	//Classe para a cria��o de ru�do de perlin (Perlin Noise)
	module::Perlin myModule;

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(512, 256);
	heightMapBuilder.SetBounds(-90.0, 90.0, -180.0, 180.0);
	heightMapBuilder.Build();

	return heightMap;
}


void RenderHeightMap(utils::NoiseMap heightMap, std::string filename){
	//Renderizando...
   utils::RendererImage renderer;
   utils::Image image;
   renderer.SetSourceNoiseMap (heightMap);
   renderer.SetDestImage (image);
 
   //Para definir faixas de cores... 
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
  renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow

   renderer.EnableLight ();
   renderer.SetLightContrast (3); // Triple the contrast
   renderer.SetLightBrightness (2); // Double the brightness

   renderer.Render ();

   //Escrevendo...
   utils::WriterBMP writer;
   writer.SetSourceImage (image);
   writer.SetDestFilename (filename.c_str());
   writer.WriteDestFile ();
}

int main (int argc, char** argv)
{
	utils::NoiseMap heightMap;
	
	float bounds[4] = {2.0, 6.0, 1.0, 5.0};
	heightMap = BuildAHeightMap(512, 512, bounds);
		
	std::string file = "../exercicio_1-1.bmp";
	RenderHeightMap(heightMap,file);
	

	float bounds2[4] = {6.0, 10.0, 1.0, 5.0};
	heightMap = BuildAHeightMap(512, 512, bounds2);
		
	std::string file2 = "../exercicio_1-2.bmp";
	RenderHeightMap(heightMap,file2);
	

	float bounds3[4] = {2.0, 6.0, -3.0, 1.0};
	heightMap = BuildAHeightMap(512, 512, bounds3);
		
	std::string file3 = "../exercicio_1-3.bmp";
	RenderHeightMap(heightMap,file3);
	

	float bounds4[4] = {6.0, 10.0, -3.0, 1.0};
	heightMap = BuildAHeightMap(512, 512, bounds4);
		
	std::string file4 = "../exercicio_1-4.bmp";
	RenderHeightMap(heightMap,file4);
	

   std::cout << "Success!\n";
  
   getchar();


  return 0;
}