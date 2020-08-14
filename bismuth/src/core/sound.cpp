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

void Sound::play() {
    this->playing = true;
}

void Sound::stop() {
    this->playing = false;
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
