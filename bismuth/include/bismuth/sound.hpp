#pragma once
//#include <AL/al.h>
//#include <AL/alc.h>
#include <miniaudio/miniaudio.h>
#include <string>
#include <vector>
namespace bi {
    class Sound {
        public:
            // constructors, asssignment, destructor
            Sound();
            ~Sound();
            void init();
            unsigned int loadSound(std::string filepath);
            static void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);
            void playSound(std::string filepath);



        private:
            ma_device device;
            ma_device_config config;
            ma_decoder decoder;
            //std::vector<unsigned int> buffers;
            //ALCdevice* device;

    };
}
