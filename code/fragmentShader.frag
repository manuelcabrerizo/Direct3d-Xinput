sampler BaseTex;

struct PS_INPUT
{
    vector color : COLOR0;
    float2 base  : TEXCOORD0;
};

struct PS_OUTPUT
{
    vector diffuse : COLOR0; 
};

PS_OUTPUT Main(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT)0;
    vector b = tex2D(BaseTex, input.base); 
    output.diffuse =  b * input.color;
    return output;
}
