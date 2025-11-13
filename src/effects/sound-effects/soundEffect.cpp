#include <iostream>
#include "../../../include/effects/sound-effects/soundEffect.hpp"


SoundEffect::SoundEffect(const sf::SoundBuffer& buffer_, const std::string& name_)
    : buffer(&buffer_), sound(buffer_), name(name_)
{
}

std::unordered_map<std::string, sf::SoundBuffer> SoundEffect::sounds;

void SoundEffect::play() {
    sound.play();
}

void SoundEffect::stop() {
    sound.stop();
}

void SoundEffect::pause() {
    sound.pause();
}

void SoundEffect::playGatlingShoot(){
    static SoundEffect GatlingShootSound(getSound("gatlingShoot.wav"), "gatlingShoot");
    GatlingShootSound.setVolume(70.f);
    GatlingShootSound.play();
};

void SoundEffect::playMortarShoot(){

};

void SoundEffect::playExplosion(){

};

void SoundEffect::playBeam(){

};

void SoundEffect::playSpawn(){
    static SoundEffect SpawnSound(getSound("spawn.wav"), "spawn");
    SpawnSound.setVolume(70.f);
    SpawnSound.play();
};

void SoundEffect::playDespawn(){

};

void SoundEffect::playWin(){

};

void SoundEffect::playGameOver(){

};

void SoundEffect::playPlaceTower(){

};

void SoundEffect::playSellTower(){

};

void SoundEffect::playUpgardeTower(){

};

void SoundEffect::playSoundTrack1(){

};

void SoundEffect::setVolume(float volume) {
    sound.setVolume(volume);
}

void SoundEffect::setPitch(float pitch) {
    sound.setPitch(pitch);
}

void SoundEffect::setLooping(bool looping) {
    sound.setLooping(looping);
}

bool SoundEffect::isLooping() const {
    return sound.isLooping();
}

const sf::SoundBuffer& SoundEffect::getSound(const std::string& filename) {
    if (auto it = sounds.find(filename); it != sounds.end())
        return it->second;

    sf::SoundBuffer snd;
    if (!snd.loadFromFile("../assets/sounds/" + filename)) {
        std::cerr << "[Renderer] Missing sound: " << filename << std::endl;
    }   
    auto [insertedIt, _] = sounds.emplace(filename, std::move(snd));
    return insertedIt->second;
}

sf::Sound::Status SoundEffect::getStatus() const {
    return sound.getStatus();
}

const std::string& SoundEffect::getName() const {
    return name;
}
