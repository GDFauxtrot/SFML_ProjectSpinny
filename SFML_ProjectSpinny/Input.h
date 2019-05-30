#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
using string = std::string;

/// Input is responsible for abstracting game input. SFML
/// provides a well enough input system, but it would
/// be preferrable to ask for inputs in the game
/// that correspond to actions (GetButtonDown("Action")),
/// rather than hard coding the inputs.

enum InputType { Keyboard, MouseButton, MouseScroll };

class Input
{
private:
    /// A bit of data to hold info for inputs: SFML enums can be
    /// stored as general ints, categorized by InputType.
    struct InputInfo
    {
        InputType type;
        int enumId;
    };

    /// The defaults for this game. Hard-coded so it can't get lost
    static const std::map<string, InputInfo> defaults;
    
    /// The current key configuration set up
    static std::map<string, InputInfo> keyInfo;

    static float wheelDelta;

    // List of held buttons this frame
    static std::vector<InputInfo> pressedInputs;
    // List of released buttons this frame
    static std::vector<InputInfo> releasedInputs;

    /// Translates into according input checks for supported inputs
    static bool getInputInfoButton(InputInfo input);

public:
    /// Given an SFML event, process if it's an input event (pressed/released)
    static void handleEvent(sf::Event event);

    /// Updates the input state at the start of the frame
    static void update();

    /// Returns true if the given name corresponds to a pressed input
    static bool getButton(string b);

    /// Returns if the given name's button was pressed this frame
    static bool getButtonDown(string b);

    /// Returns if the given name's button was released this frame
    static bool getButtonUp(string b);
};