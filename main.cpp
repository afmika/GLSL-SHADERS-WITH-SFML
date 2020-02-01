#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;

const int width = 800;
const int height = 500;

int ms_time = 1000/40;

sf::Sprite sprite;
sf::Texture texture;
sf::Shader shader;
sf::RenderStates states;
float t = 0;


sf::VertexArray points;

bool load_ok = false;

// test 1
void load_one() {
    bool img_loaded = texture.loadFromFile("images/filo.jpg");
    // on specifie que l'on utilise un frag shader
    bool shader_loaded = shader.loadFromFile("shaders/pixelate.frag", sf::Shader::Fragment);
    load_ok = img_loaded && shader_loaded;
    states.shader = &shader;
}
void test_one(float x, float y, sf::RenderWindow &window) {

    if ( load_ok ) {
        x = x / window.getSize().x;
        y = y / window.getSize().y;
        shader.setUniform("texture", sf::Shader::CurrentTexture);
        shader.setUniform("pixel_threshold", ((x + y) / 30) ); // niveau de pixelisation
        
        sprite.setTexture( texture );
        window.draw(sprite, states);
        return;
    }
}

// test 2
void load_two() {
    bool img_loaded = texture.loadFromFile("images/test.png");
    // on specifie que l'on utilise un frag shader UNIQUEMENT
    bool shader_loaded = shader.loadFromFile("shaders/space.frag", sf::Shader::Fragment);
    load_ok = img_loaded && shader_loaded;
    states.shader = &shader;
}
void test_two(float x, float y, sf::RenderWindow &window) {
    if ( load_ok ) {
        sf::Color c = sf::Color::Magenta;
        shader.setUniform("lightOrigin", sf::Vector2f(x, y)); //  uniform vec2 lightOrigin
        shader.setUniform("lightColor", sf::Vector3f(c.r, c.g, c.b)); //  uniform vec3 lightColor
        shader.setUniform("lightAttenuation", 100.0f); // uniform float lightAttenuation
        shader.setUniform("screenResol", sf::Vector2f(width, height)); // uniform vec2 screenResol
        shader.setUniform("texture", sf::Shader::CurrentTexture); // uniform sampler2D texture

        sprite.setTexture( texture );
        window.draw(sprite, states);
        return;
    }
}

// test 3
void load_three() {
    // l'ordre est important : vert puis frag
    load_ok = shader.loadFromFile("shaders/storm.vert", "shaders/blink.frag");
    states.shader = &shader;
    for (int i = 0; i < 20000; ++i) {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White));
    }
}
void test_three(float x, float y, sf::RenderWindow &window) {
    if ( load_ok ) {
        // permet de faire osciller le rayon
        float radius = 200 + cos(t) * 150;
        shader.setUniform("storm_position", sf::Vector2f(x, y));
        shader.setUniform("storm_inner_radius", radius / 3);
        shader.setUniform("storm_total_radius", radius);

        // cos va faire osciller la luminosite
        shader.setUniform("blink_alpha", (float)( 0.5f + cos(t) * 0.25f));
        shader.setUniform("texture", sf::Shader::CurrentTexture);

        window.draw(points, states);
        return;
    }
}


// test 4
void load_four() {
    // l'ordre est important : vert puis frag
    load_ok = shader.loadFromFile("shaders/tests/effect.1.vert", "shaders/tests/effect.1.frag");
    states.shader = &shader;
    for (int i = 0; i < 20000; ++i) {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White));
    }
}
void test_four(float x, float y, sf::RenderWindow &window) {
    if ( load_ok ) {
        // permet de faire osciller le rayon
        window.draw(points, states);
        return;
    }
}


// test 5
void load_five() {
    bool img_loaded = texture.loadFromFile("images/filo.jpg");
    sprite.setTexture( texture );

    // on specifie que l'on utilise un frag shader
    bool shader_loaded = shader.loadFromFile("shaders/tests/flashlight.frag", sf::Shader::Fragment);
    load_ok = img_loaded && shader_loaded;
    states.shader = &shader;
    cout << "HERE" << endl;
}
void test_five(float x, float y, sf::RenderWindow &window) {
    if ( load_ok ) {
        y = height - y;

         float radius = 150 + cos(t) * 100;
        sf::Vector3f vec_color(10, 10, 10);
        float alpha = 1;

        shader.setUniform("texture", sf::Shader::CurrentTexture);
        shader.setUniform("pos_mouse", sf::Vector2f(x, y));
        shader.setUniform("radius", radius);
        shader.setUniform("back_color",  vec_color);
        shader.setUniform("alpha",  alpha);
        
        window.draw(sprite, states);
        return;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "TEST SHADER", sf::Style::Titlebar | sf::Style::Close);

    void (*test_func)(float, float, sf::RenderWindow&);
    load_five();
    test_func = test_five;
    sf::Clock clock;
    while(window.isOpen()) {
        sf::Event e;
        float x = static_cast<float>(sf::Mouse::getPosition(window).x);
        float y = static_cast<float>(sf::Mouse::getPosition(window).y);

        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            if(e.type == sf::Event::MouseMoved) {
               // cout << x << " : " << y << endl;
            }
        }

        test_func(x, y, window);
        t = clock.getElapsedTime().asSeconds();

        window.display();
        window.clear();
        sf::sleep(sf::milliseconds(ms_time));
    }
    return 0;
}
