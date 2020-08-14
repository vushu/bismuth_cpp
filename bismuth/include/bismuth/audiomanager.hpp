#pragma once
#include <memory>
#include <miniaudio/miniaudio.h>
#include <bismuth/sound.hpp>
#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000
namespace bi  {
    class AudioManager {

        public:
            // constructors, asssignment, destructor
            AudioManager ();
            ~AudioManager ();
            void init();
            unsigned int addSound(std::shared_ptr<Sound> sound);
            Sound& getSound(unsigned int soundId);

            void start();
            void stop();

        private:
            bool deviceStopped = true;
            static float volumeLimit;
            ma_event stopEvent;
            ma_device_config deviceConfig;
            ma_device device;
            static void simpleCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            static ma_uint32 readMixPcmFrames(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount, float volume);
            static std::vector<std::shared_ptr<Sound>> sounds;

    };
}
