
#include<SFML/Graphics.hpp>

class Mushroom{

  public:
    Mushroom();
    ~Mushroom();

    void Update();
    void Render(sf::RenderWindow &window);
  private:

    void Move();

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::Vector2f m_increment;
};
///////////////  构造 / 析构函数  /////////////////
Mushroom::Mushroom(){

	m_texture.loadFromFile("Mushroom.png");
	m_sprite.setTexture(m_texture);
	m_increment = sf::Vector2f(4.0f, 4.0f);
}
Mushroom::~Mushroom(){   }
/////////////////  update and render ///////////////
void Mushroom::Update(){
    Move();
}
void Mushroom::Render(sf::RenderWindow &window){
    window.draw(m_sprite);
}
////////////////////  move /////////////////
void Mushroom::Move(){
    sf::Vector2u windowSize = sf::Vector2u(640, 480);
    sf::Vector2u mushroomSize = m_texture.getSize();

    if((m_sprite.getPosition().x + mushroomSize.x > windowSize.x && m_increment.x > 0) || 
        (m_sprite.getPosition().x < 0 && m_increment.x < 0)){
            m_increment.x = -m_increment.x;
        }
    if((m_sprite.getPosition().y + mushroomSize.y > windowSize.y && m_increment.y > 0) || 
        (m_sprite.getPosition().y < 0 && m_increment.y < 0)){
            m_increment.y = -m_increment.y;
        }

    m_sprite.setPosition(m_sprite.getPosition() + m_increment);
}