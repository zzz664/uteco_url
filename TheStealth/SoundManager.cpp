#include "SoundManager.h"

#pragma comment(lib, "fmodex_vc.lib")

SoundManager::SoundManager()
{
	distance_factor = 1.0f;
	doppler_scale = 1.0f;
	rollOff_scale = 1.0f;
}

SoundManager::~SoundManager()
{
	for (int i = 0; i < SOUND_ID::ID_END; ++i)
	{
		sounds[i]->release();
	}

	delete[] sounds;
	delete[] channels;

	system->close();
	system->release();
}

SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}

void SoundManager::Initialize()
{
	FMOD_RESULT      result;
	int              numdrivers;
	unsigned int     version;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS        caps;
	char             name[256];

	result = FMOD::System_Create(&system);

	result = system->getVersion(&version);

	result = system->getNumDrivers(&numdrivers);

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	}

	else
	{
		result = system->getDriverCaps(0, &caps, 0, &speakermode);

		result = system->setSpeakerMode(speakermode);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = system->setDSPBufferSize(1024, 10);
		}

		result = system->getDriverInfo(0, name, 256, 0);

		if (strstr(name, "SigmaTel"))
		{
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
		}
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}

	system->set3DSettings(doppler_scale, distance_factor, rollOff_scale);

	sounds = new FMOD::Sound*[SOUND_ID::ID_END];
	channels = new FMOD::Channel*[SOUND_ID::ID_END];

	for (int i = 0; i < SOUND_ID::ID_END; ++i)
	{
		channels[i]->setVolume(1.0f);
	}
}
void SoundManager::Update()
{
	system->set3DSettings(doppler_scale, distance_factor, rollOff_scale);

	system->update();
}

void SoundManager::AddSound2D(SOUND_ID sound_id, FMOD_MODE mode, string path)
{
	system->createSound(path.c_str(), FMOD_HARDWARE | FMOD_2D, NULL, &sounds[sound_id]);
	sounds[sound_id]->setMode(mode);
}

void SoundManager::AddSound3D(SOUND_ID sound_id, FMOD_MODE mode, string path, float min, float max)
{
	system->createSound(path.c_str(), FMOD_HARDWARE | FMOD_3D, NULL, &sounds[sound_id]);
	sounds[sound_id]->set3DMinMaxDistance(min * distance_factor, max * distance_factor);
	sounds[sound_id]->setMode(mode);
}

void SoundManager::SetSoundPosition(SOUND_ID sound_id, float x, float y, float z)
{
	FMOD_VECTOR position = { x * distance_factor, y * distance_factor, z * distance_factor };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	channels[sound_id]->set3DAttributes(&position, &vel);
}

void SoundManager::SoundLoop(SOUND_ID sound_id, float startTime, float endTime)
{
	unsigned int currentPosition;
	channels[sound_id]->getPosition(&currentPosition, FMOD_TIMEUNIT_MS);

	if (currentPosition >= (int)(endTime * 1000))
	{
		channels[sound_id]->setPosition((int)(startTime * 1000), FMOD_TIMEUNIT_MS);
	}

}

void SoundManager::SetVolume(SOUND_ID sound_id, float volume)
{
	channels[sound_id]->setVolume(volume);
}

void SoundManager::Play(SOUND_ID sound_id)
{
	system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, &channels[sound_id]);
}

void SoundManager::PlayIs(SOUND_ID sound_id)
{
	bool isPlaying;
	channels[sound_id]->isPlaying(&isPlaying);
	if (!isPlaying)
	{
		system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, &channels[sound_id]);
	}
}

void SoundManager::Stop(SOUND_ID sound_id)
{
	channels[sound_id]->stop();
}

FMOD::System* SoundManager::GetSystem()
{
	return system;
}

FMOD::Channel* SoundManager::GetChannel(SOUND_ID sound_id)
{
	return channels[sound_id];
}