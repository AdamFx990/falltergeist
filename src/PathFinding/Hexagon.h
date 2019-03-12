/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_HEXAGON_H
#define FALLTERGEIST_HEXAGON_H

// C++ standard includes
#include <array>
#include <list>

// Falltergeist includes
#include "../Game/Object.h"
#include "../Graphics/Point.h"

// Third party includes


#define HEX_SIDES 6
#define HEX_WIDTH 16
#define HEX_HEIGHT 12

namespace Falltergeist
{
namespace Game
{
    class Object;
}

using Graphics::Point;

class Hexagon
{
public:
    // ctors
    Hexagon();
    Hexagon(unsigned int number);

    const Point& position() const;
    void setPosition(const Point& pos);

    inline bool inRender()
    { return _inRender; }
    inline void setInRender(bool value)
    { _inRender = value; }

    inline unsigned int number()
    { return _number; }
    inline void setNumber(unsigned int value)
    { _number = value; }

    inline unsigned int heuristic()
    { return _heuristic; }
    inline void setHeuristic(unsigned int value)
    { _heuristic = value; }
    // Cube X
    inline int cubeX()
    { return _cubeX; }
    inline void setCubeX(unsigned int value)
    { _cubeX = value; }
    // Cube Y
    inline int cubeY()
    { return _cubeY; }
    inline void setCubeY(unsigned int value)
    { _cubeY = value; }
    // Cube Z
    inline int cubeZ()
    { return _cubeZ; }
    inline void setCubeZ(unsigned int value)
    { _cubeZ = value; }
    // Light
    inline unsigned int light()
    { return _light; }
    unsigned int addLight(unsigned int light);
    unsigned int subLight(unsigned int light);
    unsigned int setLight(unsigned int light);

    bool canWalkThru();

    std::array<Hexagon*, HEX_SIDES>& neighbors();

    std::list<Game::Object*>* objects();

    Game::Orientation orientationTo(Hexagon *hexagon);

protected:
    std::array<Hexagon*, HEX_SIDES> _neighbors;
    std::list<Game::Object*> _objects;
    unsigned int _number = 0; // position in hexagonal grid

    Point _position;

    int _cubeX = 0;
    int _cubeY = 0;
    int _cubeZ = 0;

    unsigned int _heuristic = 0;

    bool _inRender = false;

    unsigned int _light = 655;
};

}
#endif // FALLTERGEIST_HEXAGON_H
