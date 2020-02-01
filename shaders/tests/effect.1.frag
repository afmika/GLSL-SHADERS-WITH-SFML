void main()
{
    vec4 coul = gl_Color;
    coul[2] = 255;
    gl_FragColor = coul;
    gl_FrontColor = gl_Color;
}