float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4 lightPosition;
float4 ambientColor;

texture defaultMap;
sampler diffuseSampler = sampler_state
{
	Texture = <defaultMap>;
	MipFilter = Linear;
	MinFilter = Linear;
	MagFilter = Linear;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 diffuse : TEXCOORD1;
	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
};

struct PS_INPUT
{
	float2 tex : TEXCOORD0;
	float3 diffuse : TEXCOORD1;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	Output.position = mul( Input.position, worldMatrix );
	
	float3 lightDirection = Output.position.xyz - lightPosition.xyz;

	float3 viewDir = normalize(Output.position.xyz - cameraPosition);
	Output.viewDir = viewDir;

	Output.position = mul( Output.position, viewMatrix );
	Output.position = mul( Output.position, projectionMatrix);

	lightDirection = normalize( lightDirection );

	float3 worldNormal = mul( Input.normal, (float3x3)worldMatrix );

	worldNormal = normalize( worldNormal );
	
	Output.diffuse = dot( -lightDirection, worldNormal );
	Output.reflection = reflect(lightDirection, worldNormal);

	Output.tex = Input.tex;

	return Output;
}

float4 ps_main( PS_INPUT Input ) : COLOR
{
	float3 diffuse = saturate( Input.diffuse ) * 0.5 + 0.5;

	float4 tex = tex2D( diffuseSampler, Input.tex);

	return tex * ambientColor * float4( diffuse, 1 );
}

technique DiffuseTexture
{
	pass P0
	{
		vertexShader = compile vs_3_0 vs_main();
		pixelShader = compile ps_3_0 ps_main();
	}
}