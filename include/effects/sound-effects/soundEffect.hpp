#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

/**
 * @class SoundEffect
 * @brief Represents a single, configurable sound effect.
 *
 * The SoundEffect class does not load files directly.
 * It uses an existing sf::SoundBuffer (from Renderer)
 * and controls playback, pitch, looping, and volume.
 */
class SoundEffect {
private:
    const sf::SoundBuffer* buffer; ///< Pointer to shared audio data
    sf::Sound sound;               ///< Instance that plays the sound
    std::string name;              ///< Optional name for identification

    /// @brief Sound cache to avoid redundant disk loads.
    static std::unordered_map<std::string, sf::SoundBuffer> sounds;

public:
    /**
     * @brief Constructs a sound effect using an existing SoundBuffer.
     * @param buffer_ Reference to a preloaded SoundBuffer (from Renderer)
     * @param name_ Optional name for identification
     */
    explicit SoundEffect(const sf::SoundBuffer& buffer_, const std::string& name_ = "");

    /// @brief Starts playback of the sound.
    void play();

    /// @brief Stops playback immediately.
    void stop();

    /// @brief Pauses playback (can be resumed with play()).
    void pause();

    static void playGatlingShoot();
    static void playMortarShoot();
    static void playExplosion();
    static void playBeam();
    static void playSpawn();
    static void playDespawn();
    static void playWin();
    static void playGameOver();
    static void playPlaceTower();
    static void playSellTower();
    static void playUpgardeTower();
    static void playSoundTrack1();



    /// @brief Sets the playback volume (0–100).
    void setVolume(float volume);

    /// @brief Sets the pitch (1.0 = normal speed).
    void setPitch(float pitch);

    /// @brief Enables or disables looping.
    void setLooping(bool looping);

    /// @brief Returns true if looping is enabled.
    bool isLooping() const;

    /// @brief Loads and caches a sound.
    /// @param filename File name (relative to the sounds directory).
    /// @return A const reference to the loaded sound.
    [[nodiscard]] static const sf::SoundBuffer& getSound(const std::string& filename);

    /// @brief Returns the current playback status (Playing, Paused, or Stopped).
    sf::Sound::Status getStatus() const;

    /// @brief Returns the sound’s assigned name.
    const std::string& getName() const;
};

#endif // SOUND_EFFECT_HPP
