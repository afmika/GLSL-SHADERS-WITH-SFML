uniform sampler2D texture;
uniform vec3 couleur;

void main() {
    vec4 pixel = gl_Color;
    vec4 temp = pixel + vec4(couleur.x, couleur.y, couleur.z, 1);

    vec2 pos = gl_TexCoord[0].xy;
    vec4 textureVers4D = texture2D(texture, pos);
    gl_FragColor = textureVers4D * temp;
}