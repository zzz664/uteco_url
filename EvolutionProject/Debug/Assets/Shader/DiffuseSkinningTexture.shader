float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;
float4x4 finalTransforms[35];

float4 lightPosition;
float4 ambientColor;

texture defaultMap;

int NumVertexInfluences = 2;

sampler defaultSampler = sampler_state
{
	Texture = <defaultMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 weights : BLENDWEIGHT0;
	int4 boneIndices : BLENDINDICES0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 diffuse : TEXCOORD1;
};

struct PS_INPUT
{
	float2 tex : TEXCOORD0;
	float3 diffuse : TEXCOORD1;
};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;

	float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float lastWeight = 0.0f;
	int n = NumVertexInfluences - 1;

	for ( int i = 0; i < n; ++i )
	{
		lastWeight += Input.weights[i];
		p += Input.weights[i] * mul( Input.position, finalTransforms[Input.boneIndices[i]] );
	}

	lastWeight = 1.0f - lastWeight;

	p += lastWeight * mul( Input.position, finalTransforms[Input.boneIndices[n]] );

	p.w = 1.0f;

	Output.position = mul ( p, worldMatrix );

	float3 lightDirection = Output.position.xyz - lightPosition.xyz;

	Output.position = mul( Output.position, viewMatrix );
	Output.position = mul( Output.position, projectionMatrix);

	float3 worldNormal = mul( Input.normal, (float3x3)worldMatrix );

	worldNormal = normalize( worldNormal );

	Output.diffuse = dot( - lightDirection, worldNormal );

	Output.tex = Input.tex;

	return Output;
}

float4 ps_main( PS_INPUT Input ) : COLOR
{
	float3 diffuse = saturate( Input.diffuse ) * 0.5 + 0.5;

	float4 tex = tex2D( defaultSampler, Input.tex );

	return tex * ambientColor * float4(diffuse, 0);
}

technique DiffuseSkinningTexture
{
	pass P0
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}