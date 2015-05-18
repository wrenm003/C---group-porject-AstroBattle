//
//  CollisionManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
        
        Vector2D layerPos = pTileLayer->getPosition();
        
        int x, y, tileColumn, tileRow, tileid = 0;
        
        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();
        
        if(pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
        {
            tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        else if(pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
        {
            tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
            tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        
        if(tileid != 0)
        {
            pPlayer->collision();
        }
    }
}