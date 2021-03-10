// uniforms variables:
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

vector lightDirection;

struct VS_INPUT
{
    vector position : POSITION;
    float2 tex      : TEXCOORD0;
    vector normal   : NORMAL;
};

struct VS_OUTPUT
{
    vector position : POSITION;
    float2 tex      : TEXCOORD0;
    vector color    : COLOR0;
};

VS_OUTPUT Main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.position = mul(input.position, WorldMatrix);
    output.position = mul(output.position, ViewMatrix);
    output.position = mul(output.position, ProjMatrix);
    output.tex = input.tex;
    
    lightDirection.w = 0.0f;
    input.normal.w = 0.0f;
    input.normal = mul(input.normal, WorldMatrix);

    vector diffuseLightIntensity = {1.0f, 1.0f, 1.0f, 1.0f};
    vector ambientLightIntensity = {0.2f, 0.2f, 0.2f, 1.0f};
    vector diffuseMtrl = {1.0f, 1.0f, 1.0f, 1.0f};
    vector ambientMtrl = {1.0f, 1.0f, 1.0f, 1.0f}; 

    float shadow = dot(lightDirection, input.normal);
    if(shadow < 0.0f)
    {
        shadow = 0.0f;
    }

    output.color = (ambientMtrl * ambientLightIntensity) + (shadow * (diffuseMtrl * diffuseLightIntensity));
    return output;
}
