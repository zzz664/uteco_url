float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4 cameraPosition;

float time;

float2 texScale = float2( 25, 26 );

float waveFreq = 0.028;
float waveAmp = 1.8;

float bumpScale = 0.4;
float2 bumpSpeed = float2( 0.0015, 0.0005 );

float4 deepColor = float4( 0.0, 0.3, 0.5, 1 );
float4 shallowColor = float4( 0.0, 0.6, 0.8, 1 );

float waterAmount = 0.3;

float4 reflectionColor = float4( 0.5, 0.5, 0.5, 1.0 );
float reflectionAmount = 1.0;
float reflectionBlur = 0.0;

float fresnelPower = 5.0;
float fresnelBias = 0.328;
float hdrMultiplier = 0.471;

texture texture0;

texture texture1;

sampler2D normalMap : TEXUNIT0 = sampler_state
{
	Texture = (texture0);
	MIPFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
};

sampler2D environmentMap : TEXUNIT0 = sampler_state
{
	Texture = (texture1);
	MIPFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
};

struct WAVE
{
	float freq;
	float amp;
	float phase;
	float2 dir;
};

struct VS_INPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

struct VS_OUTPUT {
	float4 pos : POSITION;

	float3 binormal : TEXCOORD1;
	float3 tangent : TEXCOORD2;
	float3 normal : TEXCOORD3;

	float2 bump0 : TEXCOORD0;
	float2 bump1 : TEXCOORD4;
	float2 bump2 : TEXCOORD5;

	float3 eyeDir : TEXCOORD7;
};

VS_OUTPUT vs_main(VS_INPUT In)
{
	VS_OUTPUT Out;

	#define NWAVES 2
	WAVE wave[NWAVES] = 
	{
		{ 1.0, 1.0, 0.5, float2( -1, 0 ) },
		{ 2.0, 0.5, 1.7, float2( -0.7, 0.7 ) }
	};

	wave[0].freq = waveFreq;
	wave[0].amp = waveAmp;
	wave[1].freq = waveFreq * 3.0;
	wave[1].amp = waveAmp * 0.33;

	
	float ddx = 0.0;
	float ddy = 0.0;
	float deriv;

	float angle;
	for(int i = 0; i < NWAVES; ++i)
	{
		angle = dot( wave[i].dir, In.pos.xz ) * wave[i].freq + time * wave[i].phase;
		In.pos.y += wave[i].amp * sin( angle );

		deriv = wave[i].freq * wave[i].amp * cos( angle );
		ddx -= deriv * wave[i].dir.x;
		ddy -= deriv * wave[i].dir.y;
	}

	Out.binormal.xyz = bumpScale * normalize( float3( 1, ddy, 0 ) ); 	//Binormal
	Out.tangent.xyz = bumpScale * normalize( float3( 0, ddx, 1) ); 	//Tangent 
	Out.normal.xyz = normalize( float3( ddx, 1, ddy ) );			//Normal;

	Out.pos = mul( In.pos, worldMatrix );
	Out.pos = mul( Out.pos, viewMatrix );
	Out.pos = mul( Out.pos, projectionMatrix );

	Out.bump0.xy = In.tex * texScale + time * bumpSpeed;
	Out.bump1.xy = In.tex * texScale * 2.0 + time * bumpSpeed * 4.0;
	Out.bump2.xy = In.tex * texScale * 4.0 + time * bumpSpeed * 8.0;

	Out.eyeDir = Out.pos.xyz - cameraPosition;

	return Out;
}

float4 ps_main(VS_OUTPUT In) : COLOR 
{
	float4 t0 = tex2D( normalMap, In.bump0 ) * 2.0 - 1.0;
	float4 t1 = tex2D( normalMap, In.bump1 ) * 2.0 - 1.0;
	float4 t2 = tex2D( normalMap, In.bump2 ) * 2.0 - 1.0;

	float3 normal = t0.xyz + t1.xyz + t2.xyz;

	float3x3 m;
	m[0] = In.binormal;
	m[1] = In.tangent;
	m[2] = In.normal;

	normal = normalize( mul( normal, m ) );

	float3 eyeDir = normalize( In.eyeDir );


	float4 R;	
	R.xyz = reflect( eyeDir, normal );

	R.z = -R.z;
	R.w = reflectionBlur;
	
	float4 reflection = tex2Dbias( environmentMap, R );
	reflection.rgb *= ( reflection.r + reflection.g + reflection.b ) * hdrMultiplier;


	float facing = 1.0 - max( dot( -eyeDir, normal ), 0 );

	float fresnel = saturate( fresnelBias + pow( facing, fresnelPower ) );

	float4 waterColor = lerp( shallowColor, deepColor, facing ) * waterAmount;

	reflection = lerp( waterColor, reflection * reflectionColor, fresnel ) * reflectionAmount;

	return (waterColor + reflection);
}

technique Water 
{
	pass P0 
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}