#include "Cell.h"
#include <cassert>
#include <limits>

Cell::Cell(size_t index) :
    index(index)
{
}


Cell::Cell(size_t x, size_t y)
{
    if (x >= 8)
    {
        index = std::numeric_limits<size_t>::max();
        return;
    }

    if (y >= 8)
    {
        index = std::numeric_limits<size_t>::max();
        return;
    }    

    index = x + y * 8;
}

Cell::Cell(int x, int y)
{
    index = x + y * 8;
}

Cell::Cell(const std::string& pos)
{
    size_t x = static_cast<int>(pos[0] - 'a');  
    size_t y = static_cast<int>(pos[1] - '1');

    *this = Cell{x, y};
}

bool Cell::isValid() const
{
    return index < 8 * 8;
}

bool Cell::fromPos(size_t x, size_t y)
{
    *this = Cell{x, y};
    return isValid();
}

bool Cell::fromPos(const std::string& pos)
{
    if (pos.size() != 2)
    {
        // Ill formed position.
        index = std::numeric_limits<size_t>::max();
    }  
    else
    {
        size_t x = static_cast<int>(pos[0] - 'a');  
        size_t y = static_cast<int>(pos[1] - '1');

        *this = Cell{x, y};
    }

    return isValid();    
}

std::string Cell::toPos() const
{
    std::string result;

    if (isValid() == false)
    {
        assert(isValid());
        return result;
    }

    size_t x = index % 8;
    size_t y = index / 8;

    result += 'a' + x;
    result += '1' + y;

    return result;
}    

size_t Cell::getIndex() const
{
    assert(isValid());
    return index;
}

void Cell::setIndex(size_t value)
{
    assert(value < 64);
    index = value;
}

Cell::operator size_t() const
{
    assert(isValid());
    return index;
}

bool Cell::operator==(const Cell& cell)
{
    return index == cell.index;
} 

// Cell Cell::operator+(const Cell& that)
// {
//     return Cell(this->index + that.index);
// } 

size_t Cell::x() const
{
    assert(isValid()); 
    return index % 8;
}

size_t Cell::y() const
{
    assert(isValid()); 
    return index / 8;
}
