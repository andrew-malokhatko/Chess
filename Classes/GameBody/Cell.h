#pragma once
#include <string>

class Cell
{
public:
    Cell() = default;
    explicit Cell(size_t index);
    explicit Cell(size_t x, size_t y);
    explicit Cell(int x, int y);
    explicit Cell(const std::string& pos);

    bool isValid() const;

    bool fromPos(size_t x, size_t y);
    bool fromPos(const std::string& pos);
    std::string toPos() const;

    size_t getIndex() const;
    void setIndex(size_t value);

    operator size_t () const;
    bool operator==(const Cell& cell);
    //Cell operator+(const Cell& cell);

    size_t x() const;   // 0-based
    size_t y() const;   // 0-based

private:
    size_t index = 0;
};

