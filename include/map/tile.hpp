#ifndef TILE_HPP
#define TILE_HPP

class Tile {
private:
    // Coordinates
    int x;
    int y;
    
public:
    Tile(int x_, int y_);
    virtual ~Tile() = default;

    virtual bool isWalkable() const = 0;
    virtual bool isBuildable() const = 0;

    int getX() const;
    int getY() const;
};

#endif // TILE_HPP
