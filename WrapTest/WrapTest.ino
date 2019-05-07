//
//  Copyright (C) 2019 Pharap (@Pharap)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <Arduboy2.h>

Arduboy2 arduboy;

#include "Images.h"

struct Camera
{
	static constexpr uint8_t width = WIDTH;
	static constexpr uint8_t height = HEIGHT;

	Point position;
	
	constexpr uint8_t getWidth() const
	{
		return width;
	}
	
	constexpr uint8_t getHeight() const
	{
		return height;
	}
	
	constexpr int16_t getLeft() const
	{
		return this->position.x;
	}
	
	constexpr int16_t getTop() const
	{
		return this->position.y;
	}
	
	constexpr int16_t getRight() const
	{
		return (this->position.x + width);
	}
	
	constexpr int16_t getBottom() const
	{
		return (this->position.y + height);
	}
};

Camera camera;

constexpr size_t backgroundWidth = 64;
constexpr size_t backgroundHeight = 64;

void drawBackgroundSection(int16_t x, int16_t y)
{
	Sprites::drawOverwrite(x, y, backgroundTile1, 0);
	Sprites::drawOverwrite(x + backgroundWidth, y, backgroundTile2, 0);
}

bool debugDraw = false;

void drawBackground()
{	
	constexpr int16_t tileWidth = backgroundWidth;
	constexpr int16_t tileHeight = backgroundHeight;
	
	const int16_t left = (camera.getLeft() / tileWidth);
	const int16_t leftOffset = (camera.getLeft() % tileWidth);
	
	const int16_t top = (camera.getTop() / tileHeight);
	const int16_t topOffset = (camera.getTop() % tileHeight);
		
	const int16_t right = (camera.getRight() / tileWidth);
	const int16_t bottom = (camera.getBottom() / tileHeight);
	
	const int16_t height = (bottom - top);
	const int16_t width = (right - left);
	
	const int16_t yStart = (top > 0) ? 0 : -1;
	const int16_t xStart = (left > 0) ? 0 : -1;
	
	for(int16_t y = yStart; y <= height; ++y)
	{
		const int16_t drawY = ((y * tileHeight) - topOffset);
		for(int16_t x = xStart; x <= width; ++x)
		{
			const int16_t drawX = ((x * tileWidth) - leftOffset);
			
			if(debugDraw)
			{
				arduboy.drawRect(drawX, drawY, tileWidth, tileHeight);
				arduboy.setCursor(drawX, drawY);
				arduboy << drawX << ' ' << drawY;
			}
			else
			{
				Sprites::drawOverwrite(drawX, drawY, backgroundTile1, 0);
			}
		}
	}
	
	if(debugDraw)
	{
		arduboy.setCursor(0, 0);	
		arduboy << F("L ") << left << ' ' << leftOffset << '\n';
		arduboy << F("T ") << top << ' ' << topOffset << '\n';
		arduboy << F("R ") << right << '\n';
		arduboy << F("B ") << bottom << '\n';
	}
}

void setup()
{
	arduboy.begin();
}

void loop()
{
	if(!arduboy.nextFrame())
		return;
		
	arduboy.pollButtons();
	
	if(arduboy.justPressed(A_BUTTON))
		debugDraw = !debugDraw;
	
	if(arduboy.pressed(LEFT_BUTTON))
		--camera.position.x;
	
	if(arduboy.pressed(RIGHT_BUTTON))
		++camera.position.x;
	
	if(arduboy.pressed(UP_BUTTON))
		--camera.position.y;
	
	if(arduboy.pressed(DOWN_BUTTON))
		++camera.position.y;
	
	arduboy.clear();
	
	drawBackground();
	
	arduboy.display();
}