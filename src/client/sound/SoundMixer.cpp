#include <iostream>
#include <string.h>
#include "OpusCodecManager.h"
#include "SoundMixer.h"


SoundMixer::SoundMixer()
{
	this->_codec = new OpusCodecManager();
	if (this->_codec == 0)
		throw std::exception();
}

SoundMixer::~SoundMixer()
{
	delete this->_codec;
}

int			SoundMixer::mergeVoices(short *dest, int framePerBuffer, std::map<int, SoundBuffer> &voices, int voicesCount)
{
	int				i;
    short           uncrypted[FRAMES_PER_BUFFER * NUM_CHANNELS];

	memset(this->_tmpF, 0, SOUND_SIZE_PER_SEC * sizeof(float));
	std::map<int, SoundBuffer>::iterator it = voices.begin();
    while (it != voices.end())
	{
        i = it->second.cpyEncriptedSound(this->_tmpOutput, SOUND_SIZE_PER_SEC);
		if (i != 0)
            i = this->_codec->decode(this->_tmpOutput, uncrypted, i, FRAMES_PER_BUFFER);
        if (i < FRAMES_PER_BUFFER)
        {
            memset(&uncrypted[i * NUM_CHANNELS], 0, (FRAMES_PER_BUFFER * NUM_CHANNELS - i * NUM_CHANNELS) * sizeof(short));
        }
		for (i = 0; i < framePerBuffer * NUM_CHANNELS; ++i)
            this->_tmpF[i] += (uncrypted[i] / voicesCount);
		++it;
	}
	for (i = 0; i < framePerBuffer * NUM_CHANNELS; ++i)
        dest[i] = (short)this->_tmpF[i];
	return (1);
}

int			SoundMixer::encryptInput(const short *input, int size, SoundBuffer &buff)
{
    int		esize;

    esize = this->_codec->encode(input, this->_tmpInput, size, SOUND_SIZE_PER_SEC);
    buff.pushEncriptedSound(this->_tmpInput, esize);
	return (esize);
}

