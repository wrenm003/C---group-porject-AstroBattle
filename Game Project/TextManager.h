#pragma once
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <map>
class TextManager
{
public:
	static TextManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	TextManager();
	~TextManager();

	bool loadFont(std::string fontName, std::string id, int size);
	TTF_Font* getFont(std::string id);

private:
	static TextManager* s_pInstance;
	std::map < std::string, TTF_Font* > m_fonts;
};
typedef TextManager TheTextManager;
