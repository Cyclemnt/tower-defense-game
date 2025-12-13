#include "infrastructure/sfmlResourceManager.hpp"

namespace tdg::infra {
    
    const sf::Texture& SFMLResourceManager::getTexture(const std::string& name) {
        // Check if the resource is already loaded
        if (m_textures.find(name) == m_textures.end()) {
            
            // Attempt to insert and load the resource
            sf::Texture& newTexture = m_textures[name];
            std::string path = "../assets/textures/" + name + ".png";

            if (!newTexture.loadFromFile(path)) {
                // Loading failed
                m_textures.erase(name);
                throw std::runtime_error("Failed to load texture: " + path);
            }
        }
        return m_textures.at(name);
    }

    const sf::SoundBuffer& SFMLResourceManager::getSound(const std::string& name) {
        // Check if the resource is already loaded
        if (m_soundBuffers.find(name) == m_soundBuffers.end()) {
            
            // Attempt to insert and load the sound buffer
            sf::SoundBuffer& newBuffer = m_soundBuffers[name];
            std::string path = "../assets/sounds/" + name;

            if (!newBuffer.loadFromFile(path)) {
                // Loading failed
                m_soundBuffers.erase(name);
                throw std::runtime_error("Failed to load sound buffer: " + path);
            }
        }
        return m_soundBuffers.at(name);
    }

} // namespace tdg::infra
