#include "StopState.h"

StopState::StopState(RenderHelper& _renderHelper) : State(_renderHelper) {}

bool IsStopButtonPressed()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(GetRenderHelper().GetWindow());
    auto translatedMousePosition = GetRenderHelper().GetWindow().mapPixelToCoords(mousePosition);
    return GetRenderHelper().GetStartButton().first.getGlobalBounds().contains(translatedMousePosition);
}

bool StopState::SlotsInBounds(int range) const 
{
    sf::FloatRect slotBounds = GetRenderHelper().GetSlot(range * NUM_SLOTS).sprite.getGlobalBounds(); 
    return slotBounds.left >= 90.f && slotBounds.top >= 318.f && slotBounds.left + slotBounds.width <= 90.f + 340.f && slotBounds.top + slotBounds.height <= 84.f + 318.f;
}

void CalculateScore(int range)
{
    int texturesNumber[NUM_SLOTS] = {0, 0, 0, 0, 0};
    int maxMatchTexturesNumber = 0;
                        
    for (int j = 0; j < NUM_SLOTS; ++j)
    {
        int textureIndex = GetRenderHelper().GetSlot(range * NUM_SLOTS + j).textureIndex;
        ++texturesNumber[textureIndex];
        maxMatchTexturesNumber = std::max(maxMatchTexturesNumber, texturesNumber[textureIndex]);
    }

    GetRenderHelper().UpdateScore(maxMatchTexturesNumber * 500);
}

void FindSlotsInBounds()
{
    for (int i = 4; i >= 0; --i)
    {
        if (SlotsInBounds(i)) 
        { 
            CalculateScore(i);
            break;
        }
    }
}

void StopState::Update()
{
    for (auto& slot : GetRenderHelper().GetSlots()) 
    {
        if (slot.sprite.getPosition().y >= START_LINE_Y)
        {
            GetRenderHelper().GetWindow().draw(slot.sprite);
        }
    }

    sf::Event event;

    while (GetRenderHelper().GetWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed) GetRenderHelper().GetWindow().close();
        if (event.type == sf::Event::MouseButtonPressed && IsStopButtonPressed())
        {
            FindSlotsInBounds();
            SetFinishStatus(true);
            return;
        }
    } 
}