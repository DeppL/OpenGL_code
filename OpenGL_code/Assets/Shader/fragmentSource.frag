#version 410 core

struct Material{
    vec3 ambient;
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D emissionMap;
    sampler2D normalMap;
    float shininess;
};

struct LightDiractional{
    vec3 pos;
    vec3 dirToLight;
    vec3 color;
};
struct LightPoint{
    vec3 pos;
    vec3 dirToLight;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};
struct LightSpot{
    vec3 pos;
    vec3 dirToLight;
    vec3 color;
    float cosInnerPhy;
    float cosOutterPhy;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform LightDiractional lightD;
uniform LightPoint lightP;
uniform LightSpot lightS;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
uniform float time;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;


vec3 CalcLightDirectional(LightDiractional light, vec3 uNormal, vec3 dirToCamera) {

    // diffuse max(dot(L, N), 0)
    float diffIntensity = max(dot(light.dirToLight, uNormal), 0);
    vec3 diffuseColor = diffIntensity * light.color * texture(material.diffuseMap, TexCoord).rgb;

    // specular pow(max(dot(R, Cam), 0), shininess)
    vec3 R = normalize(reflect(-light.dirToLight, uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
    vec3 specColor = specIntensity * light.color * texture(material.specularMap, TexCoord).rgb;

    vec3 result = diffuseColor + specColor;
    return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
    
    // attenuation 
    float dist = length(light.pos - FragPos);
    float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // diffuse 
    float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
    vec3 diffuseColor = diffIntensity * light.color * texture(material.diffuseMap, TexCoord).rgb;

    // specular
    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
    vec3 specColor = specIntensity * light.color * texture(material.specularMap, TexCoord).rgb;

    vec3 result = diffuseColor + specColor;
    return result;
}

vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {

    float spotRatio;
    float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);

    if(cosTheta > light.cosInnerPhy) {
        spotRatio = 1.0f;
    } else if (cosTheta > light.cosOutterPhy) {
        spotRatio = (cosTheta - light.cosOutterPhy) / (light.cosInnerPhy - light.cosOutterPhy);
    } else {
        spotRatio = 0;
    }
    
    float dist = length(FragPos - light.pos);
    float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // diffuse
    float diffIntensity = max(dot(normalize(lightS.pos - FragPos), uNormal), 0);
    vec3 diffuseColor = diffIntensity * light.color * texture(material.diffuseMap, TexCoord).rgb * attenuation * spotRatio;

    // specular
    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * spotRatio;
    vec3 specColor = specIntensity * light.color * texture(material.specularMap, TexCoord).rgb;


    vec3 result = diffuseColor + specColor;
    return result;
}


void main()
{
    vec3 finalResult = vec3(0, 0, 0);
    vec3 uNormal = normalize(Normal);
    vec3 dirToCamera = normalize(cameraPos - FragPos);
    
//    vec3 lightColor;
    // if(gl_FragCoord.x * 2 < gl_FragCoord.y + 400)
    //     lightColor = vec3(0.2f, 0.0f, 0.0f);
    // else if(gl_FragCoord.x * 2 < gl_FragCoord.y + 1200)
    //     lightColor = vec3(0.0f, 0.2f, 0.0f);
    // else
    //     lightColor = vec3(0.0f, 0.0f, 0.2f);

    finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
    if(gl_FragCoord.x < 800)
        finalResult += CalcLightPoint(lightP, uNormal, dirToCamera);
    else
        finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

    finalResult += ambientColor;
//    finalResult += lightColor;
    FragColor = vec4(finalResult, 1.0);
//    FragColor = vec4(1.0);
}




