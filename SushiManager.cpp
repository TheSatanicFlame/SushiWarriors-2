#include "SushiManager.h" // Include SushiManager.h for the SushiManager class
#include <stdlib.h> // For rand()
#include "ScoreSystem.h" // Include ScoreSystem.h for the ScoreSystem class
#include <iostream> // For std::cout

namespace Tmpl8 {

    //normal sushi sprites
    Sprite* scoreSpriteVariant1 = new Sprite(new Surface("assets/normal/1.png"), 1);
    Sprite* scoreSpriteVariant2 = new Sprite(new Surface("assets/normal/2.png"), 1);
    Sprite* scoreSpriteVariant3 = new Sprite(new Surface("assets/normal/3.png"), 1);

    //speed up sushi sprites
    Sprite* speedUpSpriteVariant1 = new Sprite(new Surface("assets/speedup/1.png"), 1);
    Sprite* speedUpSpriteVariant2 = new Sprite(new Surface("assets/speedup/2.png"), 1);
    Sprite* speedUpSpriteVariant3 = new Sprite(new Surface("assets/speedup/3.png"), 1);

    //speed down sushi sprites
    Sprite* speedDownSpriteVariant1 = new Sprite(new Surface("assets/speeddown/1.png"), 1);
    Sprite* speedDownSpriteVariant2 = new Sprite(new Surface("assets/speeddown/2.png"), 1);
    Sprite* speedDownSpriteVariant3 = new Sprite(new Surface("assets/speeddown/3.png"), 1);

    //sashimi
    Sprite* sashimiSprite = new Sprite(new Surface("assets/sashimi.png"), 1);



    //barrier
    Sprite* barrierSprite = new Sprite(new Surface("assets/milk.png"), 1);

SushiManager::SushiManager() {
    
}

SushiManager::~SushiManager() {
    // Cleanup sushiList and release resources
    for (auto sushi : sushiList) delete sushi;
    sushiList.clear();
    ClearSushi();
}

void SushiManager::Update(float deltaTime, float gameTimeRemaining) {
    // Ensure spawn rate decreases as the game progresses to increase difficulty

    // Maximum and minimum spawn intervals in seconds
    const float maxSpawnRate = 1.5f; // Maximum time between spawns at the start
    const float minSpawnRate = 0.2f; // Minimum time between spawns for highest difficulty

    // Calculate the normalized progress through the game, from 0.0 (start) to 1.0 (end)
    float progress = (180.0f - gameTimeRemaining) / 180.0f; // Assuming a 3-minute game duration

    // Calculate current spawn rate based on game progress
    // Linearly interpolate between maxSpawnRate and minSpawnRate based on progress
    float currentSpawnRate = maxSpawnRate * (1 - progress) + minSpawnRate * progress;

    // Update spawn timer
    spawnTimer -= deltaTime / 1000;
    if (spawnTimer <= 0.0f) {
        SpawnSushi(); // Spawn sushi and reset timer
        spawnTimer += currentSpawnRate; // Reset timer based on the current spawn rate
    }
}


void SushiManager::SpawnSushi() {
    // Define weights for each sushi type. Assume each pair is <SushiType, weight>
    std::vector<std::pair<SushiType, int>> weights = {
        {SPEED_UP, 10},   //spawn rate of speed up sushi
        {SPEED_DOWN, 10}, //spawn rate of speed down sushi
        {SPEED_RESET, 5}, //spawn rate of speed reset sushi
        {SCORE, 3},      //spawn rate of score sushi
        {DEFAULT, 60}     //spawn rate of normal sushi
    };

    // Calculate total weight
    int totalWeight = 0;
    for (auto& weight : weights) {
        totalWeight += weight.second;
    }

    // Generate random number within the range of total weight
    int randomNum = rand() % totalWeight;

    // Determine sushi type based on the random number
    SushiType type = DEFAULT; // Start with a default value
    for (auto& weight : weights) {
        if (randomNum < weight.second) {
            type = weight.first;
            break;
        }
        randomNum -= weight.second;
    }

    // Generate a random x position within the screen bounds
    float x = static_cast<float>(rand() % ScreenWidth); // Random x position within screen width
    // Adjust y position to start just above the screen to make sushi "fall" down
    vec2 position = vec2(x, -10.0f); // Start just above the screen
    // Default points for the sushi, can be adjusted based on the type if needed
    int points = 100;
    // Decide on the sprite based on the sushi type
    Sprite* sprite = GetSpriteForSushiType(type); // Ensure this function handles all types correctly
    // Create new sushi and add it to the list
    sushiList.push_back(new Sushi(type, position, sprite, points));
}


Sprite* SushiManager::GetSpriteForScoreSushi() {
    // Example implementation - return different sprites based on a random variant
    int variant = rand() % 3; //3 different sprites
    switch (variant) {
    case 0: return scoreSpriteVariant1; 
    case 1: return scoreSpriteVariant2;
    case 2: return scoreSpriteVariant3;
    default: return scoreSpriteVariant1; // Fallback case
    }
}

Sprite* SushiManager::GetSpriteForSpeedUpSushi() {
    int variant = rand() % 3; // 3 different sprites
    switch (variant) {
    case 0: return speedUpSpriteVariant1;
    case 1: return speedUpSpriteVariant2;
    case 2: return speedUpSpriteVariant3;
    default: return speedUpSpriteVariant1; // Fallback case
    }
}

Sprite* SushiManager::GetSpriteForSpeedDownSushi() {
    int variant = rand() % 3; // 3 different sprites
    switch (variant) {
    case 0: return speedDownSpriteVariant1;
    case 1: return speedDownSpriteVariant2;
    case 2: return speedDownSpriteVariant3;
    default: return speedDownSpriteVariant1; // Fallback case
    }
}

Sprite* SushiManager::GetSpriteResetSushi() {
    int variant = rand() % 3; // 3 different sprites
    switch (variant) {
    case 0: return barrierSprite; 
    case 1: return barrierSprite;
    case 2: return barrierSprite;
    default: return barrierSprite; // Fallback case
    }
}

Sprite* SushiManager::GetSpriteForSushiType(SushiType type) {
    // Return the appropriate sprite based on the sushi type
    switch (type) {
    case SPEED_UP: return GetSpriteForSpeedUpSushi();
    case SPEED_DOWN: return GetSpriteForSpeedDownSushi();
    case SCORE: return sashimiSprite;
    case SPEED_RESET: return GetSpriteResetSushi();
    case DEFAULT: return GetSpriteForScoreSushi();
        // Add cases for other sushi types as necessary
    default: return GetSpriteForScoreSushi(); // A default sprite if no specific type matches
    }
}

void SushiManager::UpdateSushi(float deltaTime) {
    // Iterate over each sushi in the list and update it
    for (auto& sushi : sushiList) {
        sushi->Update(deltaTime);
    }
}

void SushiManager::DrawSushi(Surface* screen) {
    // Iterate over each sushi in the list and draw it
    for (auto& sushi : sushiList) {
        sushi->Draw(screen); // Call the Draw method of each Sushi object
    }
}

void SushiManager::ClearSushi() {
    for (Sushi* sushi : sushiList) {
        delete sushi; // Delete each dynamically allocated Sushi
    }
    sushiList.clear(); // Clear the list of pointers
}


void SushiManager::CheckCollisions(Player& player) {
    float speedIncrement = 0.1f; // Speed increment for speed up/down sushi
    auto it = sushiList.begin(); // Iterator to loop through the list
    while (it != sushiList.end()) { // Loop until the end of the list
        Sushi* sushi = *it; // Get the current sushi
        if (player.CollidesWith(*sushi)) { // Check for collision with the player
            std::cout << "Collision detected! Sushi Type:" << sushi->GetType() << std::endl;
            switch (sushi->GetType()) { // Check the type of sushi
            case SushiType::SPEED_UP:
                if (player.GetSpeed() < 0.4f){ // Limit speed to 0.4f
                    player.SetSpeed(player.GetSpeed() + speedIncrement); // Increase speed
                }
                ScoreSystem::AddScore(10); // Add score
                break;
            case SushiType::SPEED_DOWN:
                if (player.GetSpeed() > 0.1f) { // Limit speed to 0.1f
					player.SetSpeed(player.GetSpeed() - speedIncrement); // Decrease speed
				}
                ScoreSystem::AddScore(5); // Add score
                break;
            case SushiType::SPEED_RESET: // Reset speed to default
                player.ResetSpeed(); // Reset speed to default
                ScoreSystem::AddScore(20); // Add score
                break;
            case SushiType::DEFAULT:
                // Make sure there's no speed adjustment logic here
                ScoreSystem::AddScore(15); // Add score
                break;
            case SushiType::SCORE:
                ScoreSystem::AddScore(150); // Add score
                break;
                // Handle other cases
            }
            // Common logic for all sushi types (e.g., remove sushi, add score)
            delete sushi;
            it = sushiList.erase(it); // Remove sushi from the list and advance iterator
        }
        else {
            ++it; // Move to the next sushi in the list
        }
    }
}

} // namespace Tmpl8
