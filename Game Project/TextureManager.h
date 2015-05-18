#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
class TextureManager
{
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	//draw static image
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//draw frame

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE, int angle = 0);
	
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);

	void clearFromTextureMap(std::string id);
	
private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance;
	TextureManager(){}
};

typedef TextureManager TheTextureManager;