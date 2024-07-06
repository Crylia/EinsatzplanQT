#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <map>

inline static const std::map<std::string, std::string>& load_config(const std::string& filename) {
	static std::map<std::string, std::string> config;
	static bool is_loaded{ false };
	static std::string fn{ "" };

	if (!is_loaded || fn != filename) {
		std::ifstream file(filename);
		std::string line;

		while (std::getline(file, line)) {
			std::istringstream line_stream(line);
			std::string key;
			if (std::getline(line_stream, key, '=')) {
				std::string value;
				if (std::getline(line_stream, value)) {
					config[key] = value;
				}
			}
		}

		is_loaded = true;
		fn = filename;
	}
	return config;
}
