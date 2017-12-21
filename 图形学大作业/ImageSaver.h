#pragma once

#include <string>

class System;

class ImageSaver
{
public:
	ImageSaver(System* system);
	~ImageSaver();
	void save(const std::string filename);
private:
	System* system;
};

