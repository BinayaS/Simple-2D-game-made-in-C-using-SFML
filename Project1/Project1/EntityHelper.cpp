#include "EntityHelper.h"

bool EntityHelper::PlaceMeeting(float x, float y, float width, float height, std::vector<Solid> solidArray)
{
    for (int i = 0; i < solidArray.size(); i++) {
        if (solidArray[i].GetBody().getGlobalBounds().contains(x, y)) {
            return true;
        }
        if (solidArray[i].GetBody().getGlobalBounds().contains(x + width, y)) {
            return true;
        }
        if (solidArray[i].GetBody().getGlobalBounds().contains(x + width, y + height)) {
            return true;
        }
        if (solidArray[i].GetBody().getGlobalBounds().contains(x, y + height)) {
            return true;
        }
    }
    return false;
}

float EntityHelper::sign(float num)
{
    return (num > 0.0f) - (num < 0.0f);
}
