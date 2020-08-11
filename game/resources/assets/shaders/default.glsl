#type vertex
#version 300 es
precision highp float;
in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoords;
in float aTexId;

uniform mat4 uProjection;
uniform mat4 uView;

out vec4 fColor;
out vec2 fTexCoords;
out float fTexId;

void main() {
    fColor = aColor;
    fTexCoords = aTexCoords;
    fTexId = aTexId;
    gl_Position = uProjection * uView * vec4(aPos, 1.0);
}

#type fragment
#version 300 es
precision highp float;
precision mediump int;
in vec4 fColor;
in vec2 fTexCoords;
in float fTexId;

uniform sampler2D uTextures[8];
//uniform sampler2D uTex;

out vec4 color;

void main () {
    //color = vec4( 0.6, 1.0, 1.0, 1.0 );
    //color = texture(uTex, fTexCoords);
    if (fTexId == 0.0f) {
        color = fColor * texture(uTextures[0], fTexCoords);
    }
    else if (fTexId == 1.0f) {
        color = fColor * texture(uTextures[1], fTexCoords);
    }
    else if (fTexId == 2.0f) {
        color = fColor * texture(uTextures[2], fTexCoords);
    }
    else if (fTexId == 3.0f) {
        color = fColor * texture(uTextures[3], fTexCoords);
    }

    else if (fTexId == 4.0f) {
        color = fColor * texture(uTextures[4], fTexCoords);
    }
    else if (fTexId == 5.0f) {
        color = fColor * texture(uTextures[5], fTexCoords);
    }

    else if (fTexId == 6.0f) {
        color = fColor * texture(uTextures[6], fTexCoords);
    }
    else if (fTexId == 7.0f) {
        color = fColor * texture(uTextures[7], fTexCoords);
    }
    else {
        color = fColor;
    }
}
