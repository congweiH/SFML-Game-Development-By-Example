#include "lib/Window.h"
#include "lib/Textbox.h"

class Game{

  public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    void RestartClock();

  public:
    // get set method
    Window* GetWindow();

  private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;    // 上一帧所花费的时间


};
////////////////////  构造 / 析构函数 ////////////////////
Game::Game() : m_window("Window", sf::Vector2u(640, 480)) {
    // setting up class members

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