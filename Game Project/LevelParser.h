#pragma once
#include "Level.h"
#include "tinyxml\tinyxml.h"
class LevelParser
{
public:
	
	Level* parseLevel(const char* levelFile);

private:

	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

	void parseTextures(TiXmlElement* pTextureRoot);

	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers);

	int m_tileSize;
	int m_width;
	int m_height;
	int m_bgR, m_bgG, m_bgB;
	int m_bgA = 255;
	int m_bgColor;
};

