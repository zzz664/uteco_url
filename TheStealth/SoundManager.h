#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include <fmod.hpp>
#include <string>

using namespace std;

#define SOUND SoundManager::GetInstance()

class SoundManager
{
public:

	enum SOUND_ID
	{
		BACKGROUND,
		JET,
		HEATSEEKING,
		LOCKON,
		MISSILE,
		ID_END
	};

private:
	FMOD::System*	system;
	FMOD::Sound**	sounds;
	FMOD::Channel** channels;

	float distance_factor;
	float doppler_scale;
	float rollOff_scale;

	SoundManager();

public:

	~SoundManager();

	static SoundManager* GetInstance();

	void Initialize();
	void Update();

	void AddSound2D(SOUND_ID sound_id, FMOD_MODE mode, string path);
	void AddSound3D(SOUND_ID sound_id, FMOD_MODE mode, string path, float min, float max);

	void SetSoundPosition(SOUND_ID sound_id, float x, float y, float z);
	void SoundLoop(SOUND_ID sound_id, float startTime, float endTime);

	void SetVolume(SOUND_ID sound_id, float volume);

	void Play(SOUND_ID sound_id);
	void PlayIs(SOUND_ID sound_id);

	void Stop(SOUND_ID sound_id);

	void SetDistanceFactor(float distanceFactor) { distance_factor = distanceFactor; }
	float GetDistanceFactor() { return distance_factor; }

	void SetDopplerScale(float doppler) { doppler_scale = doppler; }
	float GetDopplerScale() { return doppler_scale; }

	void SetRollOffScale(float rolloff) { rollOff_scale = rolloff; }
	float GetRollOffScale() { return rollOff_scale; }

public:

	FMOD::System* GetSystem();
	FMOD::Channel* GetChannel(SOUND_ID sound_id);
};

#endif