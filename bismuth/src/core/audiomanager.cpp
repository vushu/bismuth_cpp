#include <bismuth/logging.hpp>
#include <bismuth/audiomanager.hpp>
#include <algorithm>
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>
using namespace bi;



AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {
    ma_device_uninit(&device);
    log("AudioManager Destroyed");
}

//Safe volumeLimit
float AudioManager::volumeLimit = 1.5f;
std::vector<std::shared_ptr<Sound>> AudioManager::sounds;

void AudioManager::init() {
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = dataCallback;
    //deviceConfig.dataCallback      = simpleCallback;
    deviceConfig.pUserData         = NULL;

    //ma_event_init(&stopEvent);
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to init audiodevice");
    }

    log("AudioManager initialized");
}

void AudioManager::start() {
    if (deviceStopped)
    {
        if (ma_device_start(&device) != MA_SUCCESS) {
            printf("Failed to start playback device.\n");
            throw std::runtime_error("Failed to start audiodevice");
        }
        deviceStopped = false;
    }
}


void AudioManager::stop() {
    //ma_event_signal(&stopEvent);
    if (!deviceStopped) {
        if (ma_device_stop(&device) == MA_SUCCESS) {
            log("OK stopped device");
            deviceStopped = true;
        }
    }
}

unsigned int AudioManager::addSound(std::shared_ptr<Sound> sound) {
    this->sounds.push_back(std::move(sound));
    return sounds.size() - 1;
}

Sound& AudioManager::getSound(unsigned int soundId) {
    return *this->sounds.at(soundId);
}

ma_uint32 AudioManager::readMixPcmFrames(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount, float volume = 1) {
    float temp[4096];
    ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount) {
        ma_uint32 iSample;
        ma_uint32 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;

        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        framesReadThisIteration = (ma_uint32)ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration);

        if (framesReadThisIteration == 0) {
            break;
        }

        for (iSample = 0; iSample < framesReadThisIteration*CHANNEL_COUNT; ++iSample) {
            pOutputF32[totalFramesRead*CHANNEL_COUNT + iSample] += temp[iSample] * volume;
        }

        totalFramesRead += framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;  /* Reached EOF. */
        }
    }
    return totalFramesRead;
}

void AudioManager::dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

    float* pOutputF32 = (float*)pOutput;

    MA_ASSERT (pDevice->playback.format == SAMPLE_FORMAT);

    for (auto& sound : sounds) {

        if (sound->rewind) {
            ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
            sound->rewind = false;
        }
        else if (!sound->isPause && !sound->isDone) {
            //ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
            // clamping volume
            sound->volume = std::max(std::min(sound->volume, volumeLimit), 0.0f);

            ma_uint32 frameRead = readMixPcmFrames(&sound->decoder, pOutputF32, frameCount, sound->volume);
            if (frameRead < frameCount) {
                if (sound->loop) {
                    // loop sound
                    ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
                }
                else
                    sound->isDone = true;
            }
        }
    }

    (void)pInput;
}

void AudioManager::simpleCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);

    (void)pInput;
}
