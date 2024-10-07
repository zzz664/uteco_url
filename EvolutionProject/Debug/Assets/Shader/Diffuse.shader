float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4 lightPosition;
float4 ambientColor;

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float3 diffuse : TEXCOORD1;
};

struct PS_INPUT
{
	float3 diffuse : TEXCOORD1;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	Output.position = mul( Input.position, worldMatrix );
	
	float3 lightDirection = Output.position.xyz - lightPosition.xyz;

	Output.position = mul( Output.position, viewMatrix );
	Output.position = mul( Output.position, projectionMatrix);

	lightDirection = normalize( lightDirection );

	float3 worldNormal = mul( Input.normal, (float3x3)worldMatrix );

	worldNormal = normalize( worldNormal);
	
	Output.diffuse = dot( -lightDirection, worldNormal );

	return Output;
}

float4 ps_main( PS_INPUT Input) : COLOR
{
	float3 diffuse = saturate( Input.diffuse ) * 0.5 + 0.5;
	
	return ambientColor * float4(diffuse, 1);
}

technique Diffuse
{
	pass P0
	{
		vertexShader = compile vs_3_0 vs_main();
		pixelShader = compile ps_3_0 ps_main();
	}
}