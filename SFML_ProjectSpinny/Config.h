#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

/// Handles CFG (config file) loading and parsing.
class Config
{
public:
    struct Entry
    {
        // std::string section;
        std::string key;
        std::string value;
    };

    Config();
    Config(std::string path);

////////////////////////////////////////////////////////////

    /// Loads the config specified at the given path into this Config
    bool loadConfig(std::string pathToFile);

    /// Saves the config loaded in this Config to the given file
    bool saveConfig(std::string pathToFile);

////////////////////////////////////////////////////////////

    /// Returns the string value of the config key in the given section
    std::string getValueString(std::string section, std::string key);

    /// Returns the int value of the config key in the given section
    int getValueInt(std::string section, std::string key);

    /// Returns the float value of the config key in the given section
    float getValueFloat(std::string section, std::string key);

    /// Returns the bool value of the config key in the given section
    bool getValueBool(std::string section, std::string key);

    /// Returns the enum type value of the config key in the given section
    /// (used mainly for SFML input enums)
    template <typename T> T getValueEnum(std::string section, std::string key)
    {
        if (!std::is_enum<T>())
            throw "Template type is not an enumerable!";

        return static_cast<T>(getValueInt(section, key));
    }
    
////////////////////////////////////////////////////////////

    /// Saves the string value at the given section->key
    void setValueString(std::string section, std::string key, std::string value);

    /// Saves the int value at the given section->key
    void setValueInt(std::string section, std::string key, int value);

    /// Saves the float value at the given section->key
    void setValueFloat(std::string section, std::string key, float value);

    /// Saves the bool value at the given section->key
    void setValueBool(std::string section, std::string key, bool value);

////////////////////////////////////////////////////////////

private:
    static const std::map<std::string, std::vector<Entry>> defaults;

    std::map<std::string, std::vector<Entry>> entries;

    /// Trims a string's leading and trailing whitespace, no copy.
    std::string& trim(std::string& str);
};