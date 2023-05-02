#include "Window.h"
#include "Textbox.h"

class Game{

  public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    void RestartClock();

    void MoveSprite(EventDetails *details);
  public:
    // get set method
    Window* GetWindow();

  private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;    // 上一帧所花费的时间

    sf::Sprite m_sprite;
    sf::Texture m_texture;
};
////////////////////  构造 / 析构函数 ////////////////////
Game::Game() : m_window("Window", sf::Vector2u(640, 480)) {
    // setting up class members
    m_texture.loadFromFile("Assets/Mushroom.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2,m_texture.getSize().y/2);
    
    m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
    

}
Game::~Game(){ }

///////////////////  update ///////////////////f/////
void Game::Update(){

    float frametime = 1.0f / 60.0f;

    if(m_elapsed.asSeconds() >= frametime){
        m_window.Update();  // update window events

        /////////////  update here /////////////////
        // do something 60 times a second

        ///////////////////////////////////////////

        m_elapsed -= sf::seconds(frametime);
    }
}
//////////////////  render  ////////////////////////
void Game::Render(){
    m_window.BeginDraw();   // clear

    //////// draw here  ///////
    
    m_window.Draw(m_sprite);
    ///////////////////////////

    m_window.EndDraw();     // display
}

//////////////////  handleinput //////////////////
void Game::HandleInput(){

}
//////////////////  other  /////////////////////
Window* Game::GetWindow(){
    return &m_window;
}
//////////////////  clock  /////////////////////
void Game::RestartClock(){
    m_elapsed += m_clock.restart();
}
void Game::MoveSprite(EventDetails *details){
    sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
    m_sprite.setPosition(mousepos.x, mousepos.y);
    
}