#ifndef _KILLME_AUDIOMANAGER_H_
#define _KILLME_AUDIOMANAGER_H_

#include "../windows/winsupport.h"
#include "xaudiosupport.h"
#include "../resource/resource.h"
#include <xaudio2.h>
#include <memory>

namespace killme
{
    class AudioClip;
    class SourceVoice;

    /** The Audio core class */
    class AudioManager
    {
        friend SourceVoice;
    private:
        ComUniquePtr<IXAudio2> xAudio_;
        VoiceUniquePtr<IXAudio2MasteringVoice> masteringVoice_;

    public:
        /** Initializes */
        void startup();

        /** Finalizes */
        void shutdown();

        /** Returns true if the audio manager is active */
        bool isActive() const;

        /** Creates a source voice */
        std::shared_ptr<SourceVoice> createSourceVoice(const Resource<AudioClip>& clip);
    };

    extern AudioManager audioManager;
}

#endif