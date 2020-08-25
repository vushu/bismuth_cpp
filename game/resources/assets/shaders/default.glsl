#type vertex
#version 300 es
precision highp float;
precision highp int;
in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoords;
in float aTexId;
in float aType;
uniform mat4 uMvp;

out vec4 fColor;
out vec2 fTexCoords;
out float fTexId;
out float fType;

void main() {
    fColor = aColor;
    fTexCoords = aTexCoords;
    fTexId = aTexId;
    fType = aType;

    gl_Position = uMvp * vec4(aPos, 1.0);
}

#type fragment
#version 300 es
precision highp float;
precision highp int;
in vec4 fColor;
in vec2 fTexCoords;
in float fTexId;
in float fType;

uniform sampler2D uTextures[8];

out vec4 color;

void main () {
    //color = vec4( 0.6, 1.0, 1.0, 1.0 );
    //color = fColor;
    //color = texture(uTex, fTexCoords);
    //color = fColor * texture(uTextures[1], fTexCoords);
    vec4 tempColor;

    if (fTexId == 0.0f) {
        color = fColor;
    }
    else if (fTexId == 1.0f) {
        tempColor = texture(uTextures[1], fTexCoords);
    }
    else if (fTexId == 2.0f) {
        tempColor = texture(uTextures[2], fTexCoords);
    }
    else if (fTexId == 3.0f) {
        tempColor = texture(uTextures[3], fTexCoords);
    }

    else if (fTexId == 4.0f) {
        tempColor = texture(uTextures[4], fTexCoords);
    }
    else if (fTexId == 5.0f) {
        tempColor = texture(uTextures[5], fTexCoords);
    }

    else if (fTexId == 6.0f) {
        tempColor = texture(uTextures[6], fTexCoords);
    }
    else if (fTexId == 7.0f) {
        tempColor = texture(uTextures[7], fTexCoords);
    }

    if (fType == 0.0f){
        color = fColor * tempColor;
    }
    else if (fType == 1.0f){
        color = fColor * tempColor.a;
    }
}
