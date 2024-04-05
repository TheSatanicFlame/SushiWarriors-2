#pragma once
#include "sushi.h" // Assume Sushi class is available
#include "player.h" // Assume Player class is available
#include <vector> // Assume vector is available

namespace Tmpl8 {

    class SushiManager {
    public:
        SushiManager(); // Constructor
        ~SushiManager(); // Destructor

        void SpawnSushi(); //Spawn sushi
        void UpdateSushi(float deltaTime); //update sushi
        void DrawSushi(Surface* screen); // Draw all sushi objects
        void Update(float deltaTime, float gameTimeRemaining); // Updates based on time
        void CheckCollisions(Player& player); // Check for collisions with player
        void ClearSushi(); // Delete all sushi objects

    private:
        float spawnTimer = 0.0f; // Time since last spawn
        float spawnRate = 2.0f; // Initial spawn rate in seconds

        std::vector<Sushi*> sushiList; // List of sushi objects
        Sprite* GetSpriteForScoreSushi(); //get sprite for score sushi
        Sprite* GetSpriteForSushiType(SushiType type); //get sprite for sushi type
        Sprite* GetSpriteForSpeedUpSushi(); //get sprite for speed up sushi
        Sprite* GetSpriteForSpeedDownSushi(); //get sprite for speed down sushi
        Sprite* GetSpriteResetSushi(); //get sprite for reset sushi
    };

} // namespace Tmpl8