#ifndef DUMMY_H
#define DUMMY_H

#include "raylib.h"
#include <stdlib.h>

class Dummy
{
public:
    Dummy(Vector2 pos, Texture2D tex):
        worldPos{pos}, texture{tex} {} // member initializer list
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);
    float getHealth() { return health; }
    void setHealth(float health) { this->health = health; }
    float getDps() { return dps; }
    void takeDamage(float damage) { health -= damage; }

private:
    Vector2 worldPos{};
    Texture2D texture{};
    float scale = 4.0f;
    float health = 100.0f;
    float dps = 0.5f;
};

#endif
