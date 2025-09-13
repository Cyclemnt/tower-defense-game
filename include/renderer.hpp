#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:
    /* data */
    
public:
    Renderer();
    ~Renderer();

    /*
    Exemple de fonctionnement avec textures

    std::map<TileType, sf::Texture> tileTextures;
    std::map<TowerType, sf::Texture> towerTextures;

    void Renderer::draw(const Tower& tower) {
        sf::Sprite sprite;
        sprite.setTexture(towerTextures[tower.getType()]);
        sprite.setPosition(tower.getX(), tower.getY());
        window.draw(sprite);
    }

    Ou avec une classe RessourceManager :

    class ResourceManager {
    private:
        std::map<std::string, sf::Texture> textures;
    public:
        void loadTexture(const std::string& id, const std::string& filename);
        sf::Texture& getTexture(const std::string& id);
    };

    Pour permettre le fonctionnement :
    
    sprite.setTexture(resourceManager.getTexture("tower_basic"));

    */

};

#endif // RENDERER_HPP
