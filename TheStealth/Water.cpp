#include "Water.h"
#include "Camera.h"
#include "DirectX9.h"

Water::Water(Camera* camera, float waterSize)
{
	this->camera = camera;

	device = DirectX9->GetDevice();

	this->waterSize = waterSize;

	{
		device->CreateVertexBuffer(
			sizeof(WATER_VERTEX)* 4,
			0,
			(D3DFVF_XYZ | D3DFVF_TEX1),
			D3DPOOL_DEFAULT,
			&vertexBuffer,
			0);


		WATER_VERTEX vertices[4] = {
			{ -1.0f * waterSize / 2,  0.0f,  1.0f * waterSize / 2, 0.0f, 0.0f },
			{  1.0f * waterSize / 2,  0.0f,  1.0f * waterSize / 2, 1.0f, 0.0f },
			{ -1.0f * waterSize / 2,  0.0f, -1.0f * waterSize / 2, 0.0f, 1.0f },
			{  1.0f * waterSize / 2,  0.0f, -1.0f * waterSize / 2, 1.0f, 1.0f }
		};

		void* pVertices;

		vertexBuffer->Lock(0, sizeof(WATER_VERTEX) * 4, (void**)&pVertices, 0);
		memcpy(pVertices, vertices, sizeof(WATER_VERTEX) * 4);
		vertexBuffer->Unlock();
	}

	waterShader = new WaterShader(camera);
}

Water::~Water()
{
	vertexBuffer->Release();

	delete waterShader;
}

void Water::Update(float eTime)
{
	DxObject::Update(eTime);

	waterShader->Update(eTime);
}

void Water::Render()
{
	DxObject::Render();

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	device->SetFVF((D3DFVF_XYZ | D3DFVF_TEX1));

	device->SetStreamSource(0, vertexBuffer, 0, sizeof(WATER_VERTEX));

	UINT numPasses = 0;
	waterShader->Start(&numPasses);

	for (UINT i = 0; i < numPasses; ++i)
	{
		waterShader->GetShader()->BeginPass(i);
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		waterShader->GetShader()->EndPass();
	}

	waterShader->End();

}

void Water::SetWaterFreq(float freq) 
{ 
	waterFreq = freq; 
	waterShader->GetShader()->SetFloat("waterFreq", waterFreq);
}

void Water::SetWaterAmp(float amp) 
{ 
	waterAmp = amp; 
	waterShader->GetShader()->SetFloat("waterAmp", waterAmp);
}

void Water::SetTextureScale(float scale) 
{ 
	textureScale = scale; 
	waterShader->GetShader()->SetVector("texScale", &D3DXVECTOR4(textureScale, textureScale, 1.0f, 1.0f));
}

void Water::SetNormalScale(float scale) 
{ 
	normalScale = scale; 
	waterShader->GetShader()->SetFloat("bumpScale", normalScale);
}

void Water::SetNormalSpeed(float speedX, float speedY) 
{ 
	normalSpeedX = speedX;
	normalSpeedY = speedY;
	waterShader->GetShader()->SetVector("bumpSpeed", &D3DXVECTOR4(normalSpeedX, normalSpeedY, 1.0f, 1.0f));
}

void Water::SetReflectionAmount(float amount) 
{ 
	reflectionAmount = amount; 
	waterShader->GetShader()->SetFloat("reflectionAmount", amount);
}

void Water::SetWaterAmount(float amount) 
{ 
	waterAmount = amount; 
	waterShader->GetShader()->SetFloat("waterAmount", amount);
}

void Water::SetHDRMultiplier(float multiplier) 
{ 
	hdrMultiplier = multiplier; 
	waterShader->GetShader()->SetFloat("hdrMultiplier", multiplier);
}