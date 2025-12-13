#ifndef SFML_RESSOURCE_MANAGER_HPP
#define SFML_RESSOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace tdg::infra {

    class SFMLResourceManager final {
    public:
        const sf::Texture& getTexture(const std::string& name);
        const sf::SoundBuffer& getSound(const std::string& name);

    private:
        std::unordered_map<std::string, sf::Texture> m_textures;
        std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    };
    
} // namespace tdg::infra

#endif // SFML_RESSOURCE_MANAGER_HPP
