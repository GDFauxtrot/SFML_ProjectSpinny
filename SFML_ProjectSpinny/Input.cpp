#include "Input.h"

const std::map<string, Input::InputInfo> Input::defaults = 
    {
        { "Forward", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::W
        }},
        { "Backward", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::S
        }},
        { "Left", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::A
        }},
        { "Right", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::D
        }},
        { "Action", Input::InputInfo {
            InputType::MouseButton, sf::Mouse::Left
        }},
        { "Back", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::Backspace
        }},
        { "Start", Input::InputInfo {
            InputType::Keyboard, sf::Keyboard::Escape
        }}
    };

std::map<string, Input::InputInfo> Input::keyInfo = Input::defaults;

std::list<Input::InputInfo> Input::pressedInputs;
std::list<Input::InputInfo> Input::releasedInputs;

float Input::wheelDelta = 0;


bool Input::getInputInfoButton(Input::InputInfo info)
{
    switch (info.type)
    {
        case InputType::Keyboard:
            return sf::Keyboard::isKeyPressed(
                static_cast<sf::Keyboard::Key>(info.enumId));
        case InputType::MouseButton:
            return sf::Mouse::isButtonPressed(
                static_cast<sf::Mouse::Button>(info.enumId));
        case InputType::MouseScroll:
            return wheelDelta != 0;
    }
    return false;
}

bool Input::getButton(string button)
{
    try
    {
        return getInputInfoButton(keyInfo[button]);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

bool Input::getButtonDown(string button)
{
    try
    {
        for (auto input : pressedInputs)
        {
            if (input.type == keyInfo[button].type &&
                input.enumId == keyInfo[button].enumId)
                return true;
        }
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

bool Input::getButtonUp(string button)
{
    try
    {
        for (auto input : releasedInputs)
        {
            if (input.type == keyInfo[button].type &&
                input.enumId == keyInfo[button].enumId)
                return true;
        }
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

void Input::handleEvent(sf::Event event)
{
    // Handle MOUSE events - wheel, buttons

    if (event.type == sf::Event::MouseWheelScrolled)
    {
        wheelDelta = event.mouseWheel.delta;
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        pressedInputs.push_back(
            Input::InputInfo {
                InputType::MouseButton,
                event.mouseButton.button }
        );
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        releasedInputs.push_back(
            Input::InputInfo {
                InputType::MouseButton,
                event.mouseButton.button }
        );
    }

    // Handle KEYBOARD events -- pressed or released

    if (event.type == sf::Event::KeyPressed)
    {
        pressedInputs.push_back(
            Input::InputInfo {
                InputType::Keyboard,
                event.key.code }
        );
    }
    if (event.type == sf::Event::KeyReleased)
    {
        releasedInputs.push_back(
            Input::InputInfo {
                InputType::Keyboard,
                event.key.code }
        );
    }
}

void Input::update()
{
    // Clear pressed/released button lists
    releasedInputs.clear();
    pressedInputs.clear();
}