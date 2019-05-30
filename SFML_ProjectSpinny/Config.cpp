#include "Config.h"
#include <SFML/Window.hpp>

const std::map<std::string, std::vector<Config::Entry>> Config::defaults = 
    {
        {
            "Controls", std::vector<Config::Entry> {
                Config::Entry {
                    "Forward", std::to_string(sf::Keyboard::W)
                },
                Config::Entry {
                    "Backward", std::to_string(sf::Keyboard::S)
                },
                Config::Entry {
                    "Left", std::to_string(sf::Keyboard::A)
                },
                Config::Entry {
                    "Right", std::to_string(sf::Keyboard::D)
                }
            }
        }
    };

Config::Config()
{
    entries = defaults;
}

Config::Config(std::string path)
{
    loadConfig(path);
}

bool isWhitespace(char c) { return c == ' ' || c == '\t'; }


std::string& Config::trim(std::string& str) {
    // https://codereview.stackexchange.com/questions/28179/simple-cfg-parser
    auto first_non_whitespace = std::find_if_not(begin(str), end(str), isWhitespace);
    str.erase(begin(str), first_non_whitespace);

    auto last_non_whitespace = std::find_if_not(str.rbegin(), str.rend(), isWhitespace).base();
    str.erase(last_non_whitespace, end(str));

    return str;
}

////////////////////////////////////////////////////////////

bool Config::loadConfig(std::string pathToFile)
{
    entries.clear();

    std::ifstream configStream(pathToFile);

    if (!configStream.is_open())
        return false;

    std::string section;
    std::string buffer;

    while (std::getline(configStream, buffer, '\n'))
    {
        trim(buffer);

        if (buffer.length() == 0)
            continue;

        // Ignore comments
        if (buffer[0] == '#' || (buffer.length() > 1 && buffer[0] == '/' && buffer[1] == '/'))
            continue;
        
        // Section parsing
        if (buffer[0] == '[' && buffer[buffer.length()-1] == ']')
        {
            section = buffer.substr(1, buffer.length()-2);
            continue;
        }

        // Key/value parsing
        std::size_t eqPos = buffer.find('=');

        // No equals -- invalid line, keep moving
        if (eqPos == std::string::npos)
            continue;

        std::string key = buffer.substr(0, eqPos);
        std::string val = buffer.substr(eqPos+1, std::string::npos);
        trim(key);
        trim(val);

        setValueString(section, key, val);
    }

    return true;
}

bool Config::saveConfig(std::string pathToFile)
{
    try
    {
        std::ofstream configStream(pathToFile);

        for (auto entry : entries)
        {
            configStream << '[' << entry.first << ']' << std::endl;
            for (auto kv : entry.second)
            {
                configStream << kv.key << " = " << kv.value << std::endl;
            }

            configStream << std::endl;
        }
    }
    catch (std::exception e)
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////

std::string Config::getValueString(std::string section, std::string key)
{
    for (auto entry : entries[section])
    {
        // if (entry.section == section && entry.key == key)
        if (entry.key == key)
            return entry.value;
    }

    // Throw exception, returning an empty string is not a sufficient fallback
    std::stringstream ss;
    ss << "Key \"" << key << "\" not found in config section \"" << section << "\"!";
    throw ss.str();
}

int Config::getValueInt(std::string section, std::string key)
{
    return std::stoi(getValueString(section, key));
}

float Config::getValueFloat(std::string section, std::string key)
{
    return std::stof(getValueString(section, key));
}

bool Config::getValueBool(std::string section, std::string key)
{
    // Set input to lowercase. Return true if our value is "true" or "1".
    // Return false for any other values.
    std::string value = getValueString(section, key);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    return value == "true" || value == "1";
}

// Config::getValueEnum is template type, defined in header

////////////////////////////////////////////////////////////

void Config::setValueString(std::string section, std::string key, std::string value)
{
    // If section->key defined, overwrite value
    bool found = false;

    for (auto& e : entries[section])
    {
        // if (e.section == section && e.key == key)
        if (e.key == key)
        {
            e.value = value;
            found = true;
            return;
        }
    }
    
    // Add new section->key->value entry
    if (!found)
        entries[section].push_back(Config::Entry { key, value });
}

void Config::setValueInt(std::string section, std::string key, int value)
{
    setValueString(section, key, std::to_string(value));
}

void Config::setValueFloat(std::string section, std::string key, float value)
{
    setValueString(section, key, std::to_string(value));
}

void Config::setValueBool(std::string section, std::string key, bool value)
{
    setValueString(section, key, std::to_string(value));
}