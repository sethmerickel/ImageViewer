#version 150

uniform sampler2D tex;

in vec2 fragTexCoord;

out vec4 finalColor;

void main() 
{
    //vec2 size = textureSize(tex, 0);
    //finalColor = vec4(size.y, 0, 0, 1);
    finalColor = texture(tex, fragTexCoord);
    //finalColor = vec4(fragTexCoord, 0.0, 1.0);
    //finalColor = vec4(1.0, 0.0, 0.0, 1.0);
} 
