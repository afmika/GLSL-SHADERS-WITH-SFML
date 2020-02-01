
void main()
{
    vec4 sommet = gl_Vertex; // on prend le vertex
    gl_Position = gl_ProjectionMatrix * sommet; // on le projete sur l'ecran
    vec4 couleur_sommet = gl_Color;
    couleur_sommet[3] = 0.5; // on change l'opacite
    gl_FrontColor = couleur_sommet;
}
