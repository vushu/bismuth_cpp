#include <bismuth/logging.hpp>
#include <bismuth/sound.hpp>
//#include <AL/al.h>
//#include <AL/alc.h>
#include <miniaudio/miniaudio.h>
#include <stdexcept>
using namespace bi;

Sound::Sound() {}
Sound::~Sound() {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    log("Sound destroyed");
}

void Sound::dataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*) device->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, output, frameCount);
    (void)input;
}
void Sound::playSound(std::string sound) {

}

void Sound::init() {
    ma_result result = ma_decoder_init_file("resources/assets/audio/test.wav", NULL, &decoder);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("Failed to load file");
    }

    // config
    config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = decoder.outputFormat;
    config.playback.channels = decoder.outputChannels;
    config.sampleRate        = decoder.outputSampleRate;
    config.dataCallback      = dataCallback;
    config.pUserData         = &decoder;

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&decoder);
        throw std::runtime_error("Failed to init device");
    }
    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        throw std::runtime_error("Failed to start sound device");
    }

    bi::log("Sound initialized");

}
