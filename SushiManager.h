#pragma once
#include "sushi.h"
#include "player.h"
#include <vector>

namespace Tmpl8 {

    class SushiManager {
    public:
        SushiManager();
        ~SushiManager();

        void SpawnSushi();
        void UpdateSushi(float deltaTime);
        void DrawSushi(Surface* screen);
        void Update(float deltaTime, float gameTimeRemaining);
        void CheckCollisions(Player& player); // Assume Player class is available

    private:
        float spawnTimer = 0.0f; // Time since last spawn
        float spawnRate = 2.0f; // Initial spawn rate in seconds

        std::vector<Sushi*> sushiList;
        Sprite* GetSpriteForScoreSushi();
        Sprite* GetSpriteForSushiType(SushiType type);
        Sprite* GetSpriteForSpeedUpSushi();
        Sprite* GetSpriteForSpeedDownSushi();
        Sprite* GetSpriteResetSushi();
    };

} // namespace Tmpl8