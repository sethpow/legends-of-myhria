#include "Dummy.h"
#include "raymath.h"

void Dummy::Render(Vector2 knightPos)
{
    // subtract knightPos from worldPos; Dummy stays in same place when knight moves
    Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
}

Rectangle Dummy::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
    return Rectangle {
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}
