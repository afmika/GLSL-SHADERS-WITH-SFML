uniform vec2 storm_position;
uniform float storm_total_radius;
uniform float storm_inner_radius;

void main()
{
    vec4 vertex = gl_ModelViewMatrix * gl_Vertex; // homogenisation des coords
    vec2 offset = vertex.xy - storm_position; // vecteur centre vers vertex
    float len = length(offset);
    if (len < storm_total_radius)
    {
        float push_distance = storm_inner_radius + len / storm_total_radius * (storm_total_radius - storm_inner_radius);
        vertex.xy = storm_position + normalize(offset) * push_distance; // on pousse de direction normal(offset)
    }

    gl_Position = gl_ProjectionMatrix * vertex; // le coord transf reprojete a l ecran
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
