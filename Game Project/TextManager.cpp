#include "TextManager.h"

TextManager* TextManager::s_pInstance = 0;

bool TextManager::loadFont(std::string fileName, std::string id, int size)
{
	TTF_Font* font;
	font = TTF_OpenFont(fileName.c_str(), size);
	if (font == NULL)
	{
		std::cout << "Loading font: " << fileName.c_str() << " failed: ERROR - " << TTF_GetError() << std::endl;
		TTF_Quit();
		return false;
	}
	m_fonts[id] = font;
	return true;
}

TTF_Font* TextManager::getFont(std::string id)
{
	return m_fonts[id];
}


TextManager::TextManager()
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
	}
}


TextManager::~TextManager()
{
}
