#pragma once
//#include <AL/al.h>
//#include <AL/alc.h>
#include <miniaudio/miniaudio.h>
#include <string>
#include <vector>
#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000
namespace bi {
    class Sound {
        public:
            // constructors, asssignment, destructor
            Sound(std::string filepath);
            ~Sound();
            void init();
            void playSound();
            void stopSound();
            void pauseSound();
            void rewindSound();
            void setVolume(float volume);
            void incrementVolume(float volume);
            void decrementVolume(float volume);
            void setLoop(bool enable);
            void setDevice(ma_device* device);

            bool isPause = true;
            bool isDone = false;
            bool rewind = false;
            bool loop = false;

            // default volume
            float volume = 1.0f;
            ma_decoder decoder;

        private:
            bool playing = false;
            std::string filepath;
            //static ma_uint64 playHead;
            ma_decoder_config decoderConfig;
            //std::vector<unsigned int> buffers;
            //ALCdevice* device;

    };
}
