#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 origin;
uniform mat4 camRotation;
uniform float aspectRatio;
uniform float fovDist;
uniform float time;

#pragma include "hsv.incl"
#pragma include "SceneDE.incl"

void main()
{
    //Power = sin(time) * 2 + 8;
    bool collision = false;
    vec4 distance = vec4(0);
    vec3 direction =  normalize((camRotation * vec4(TexCoord.x * aspectRatio,TexCoord.y,fovDist,1)).xyz);
    vec3 position =  origin; //-vec3(sin(time/3) *28900 + 29000);
    float amount = 0;
    vec4 minDist = vec4(0,0,0,1000000);
    float iterations = 0;
    float completeDist = 0;
    while(!collision && iterations < 100) {
        distance = DistanceEstimator(position);
        position += direction * distance.w;
        collision = distance.w < 0.00001 || distance.w > 100;
        amount += (1 - amount) * 0.05;
        completeDist += distance.w;
        minDist = minDist.w < distance.w ? minDist : distance;
        iterations++;
    }
    int sky = int(distance.w > 5);
    float glowStrength = 1 - atan(minDist.w) * 0.6366;
    vec3 glowColour = vec3(0,glowStrength,0);
    vec3 skyColour = vec3(0.2,0.7,1);
    //FragColor = vec4(amount*glowStrength * minDist.rgb + (1-glowStrength) * skyColour,1);
    //FragColor = vec4(hsv2rgb(vec3(TexCoord.xy,1)),1);
    //FragColor = sky * vec4(direction,1) + (1 - sky) * vec4(1,1,1,1);
    //FragColor = vec4(amount,amount,amount,1);
    //FragColor = sky * vec4(glowColour,1) + (1 - sky) * vec4(amount,amount,amount,1);
    //FragColor = sky * vec4((glowColour) * 0.75,1) + (1-sky) * vec4(vec3(0),1);
    FragColor = vec4((1/(completeDist*0.01+1)) * GetSurfaceNormal(position),1);
    //FragColor = vec4(vec3(glowStrength),1);
}

