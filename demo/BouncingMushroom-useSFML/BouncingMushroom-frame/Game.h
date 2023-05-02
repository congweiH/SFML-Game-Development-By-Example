#include "Window.h"
#include "Mushroom.h"

class Game{

  public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    void RestartClock();

    Window* GetWindow();

  private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;    // 上一帧所花费的时间

    Mushroom m_mushroom;
};
////////////////////  构造 / 析构函数 ////////////////////
Game::Game() : m_window("BouncingMushroom-frame", sf::Vector2u(640, 480)){
    // setting up class members
    
}
Game::~Game(){ }

///////////////////  update ////////////////////////
void Game::Update(){

    float frametime = 1.0f / 60.0f;

    if(m_elapsed.asSeconds() >= frametime){
        m_window.Update();  // update window events

        /////////////  update here /////////////////
        // do something 60 times a second
        m_mushroom.Update();

        ///////////////////////////////////////////

        m_elapsed -= sf::seconds(frametime);
    }
}
//////////////////  render  ////////////////////////
void Game::Render(){
    m_window.BeginDraw();   // clear

    //////// draw here  ///////
    m_mushroom.Render(*m_window.GetRenderWindow());
    
    ///////////////////////////

    m_window.EndDraw();     // display
}

//////////////////  handleinput //////////////////
void Game::HandleInput(){
    // 处理用户输入
}
//////////////////  other  /////////////////////
Window* Game::GetWindow(){
    return &m_window;
}
//////////////////  clock  /////////////////////
void Game::RestartClock(){
    m_elapsed += m_clock.restart();
}