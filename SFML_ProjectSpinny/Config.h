#include <iostream>
#include <sstream>
#include <map>

using cfg = std::map<std::string, std::string>;

/// Config handles CFG (configuration file) parsing.

class Config
{
public:
    /// Returns the dictionary of all configuration values
    /// stored inside of the given CFG file path.
    static cfg getConfig(std::string cfgPath)
    {
        std::istringstream iss;
    }

    static bool setConfig(
        cfg config,
        std::string cfgPath);
};