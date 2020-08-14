#include <bismuth/logging.hpp>
#include <bismuth/sound.hpp>
//#include <AL/al.h>
//#include <AL/alc.h>
#include <miniaudio/miniaudio.h>
#include <stdexcept>
using namespace bi;

ma_uint64 playHead;

Sound::Sound(std::string filepath) {
    this->filepath = filepath;
    this->decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
}

Sound::~Sound() {
    ma_decoder_uninit(&decoder);
    log("Sound destroyed");
}

//void Sound::reset() {
    //this->isPause = false;
    //this->isDone = false;
//}

void Sound::playSound() {
    this->isPause = false;
}

void Sound::pauseSound() {
    this->isPause = true;
}

void Sound::stopSound() {
    this->rewindSound();
    this->isPause = true;
}

void Sound::rewindSound() {
    //this->isPause = false;
    this->isDone = false;
    this->rewind = true;
}

void Sound::incrementVolume(float volume) {
    this->volume += volume;
}

void Sound::decrementVolume(float volume) {
    this->volume -= volume;
}


void Sound::setLoop(bool enable) {
    this->loop = enable;
}

void Sound::setVolume(float volume) {
    this->volume = volume;
}

void Sound::init() {

    log("init SOUND: " + this->filepath);
    ma_result result = ma_decoder_init_file(filepath.c_str(), &decoderConfig, &decoder);


    log("done here");
    if (result != MA_SUCCESS) {
        throw std::runtime_error("Failed to load file");
    }
    bi::log("Sound initialized");

}
