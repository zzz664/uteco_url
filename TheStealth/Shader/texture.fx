float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4 color;

texture tex;
sampler texSamp = sampler_state {
	Texture = <tex>;
	ADDRESSU = CLAMP;
	ADDRESSV = CLAMP;
	MINFILTER = LINEAR;
	MIPFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

struct VS_INPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

struct VS_OUTPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

VS_OUTPUT VS_TEXTURE(VS_INPUT In) {
	VS_OUTPUT Out;

	Out.pos = mul(In.pos, worldMatrix);
	Out.pos = mul(Out.pos, viewMatrix);
	Out.pos = mul(Out.pos, projectionMatrix);

	Out.tex = In.tex;

	return Out;
}

float4 PS_TEXTURE(VS_OUTPUT In) : COLOR {
	float4 texColor = tex2D(texSamp, In.tex);
	return texColor * color;
}

technique Texture {
	pass P0 {
		VertexShader = compile vs_3_0 VS_TEXTURE();
		PixelShader = compile ps_3_0 PS_TEXTURE();
	}
}