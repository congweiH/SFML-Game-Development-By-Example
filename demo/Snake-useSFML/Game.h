#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

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

    Snake m_snake;
    World m_world;
    Textbox m_textbox;

};
////////////////////  构造 / 析构函数 ////////////////////
Game::Game() : m_window("Snake", sf::Vector2u(640, 480)), m_snake(16), m_world(sf::Vector2u(640,480)){
    // setting up class members
    // 可见行数, 字符大小, 整个文本框的宽度，在屏幕上绘制文本的位置
    m_textbox.Setup(5, 14, 270, sf::Vector2f(16, 16));
    m_textbox.Add("game start.your score:0");

}
Game::~Game(){ }

///////////////////  update ////////////////////////
void Game::Update(){

    float frametime = 1.0f / m_snake.GetSpeed();

    if(m_elapsed.asSeconds() >= frametime){
        m_window.Update();  // update window events

        /////////////  update here /////////////////
        // do something 60 times a second
        m_snake.Update(m_textbox);
        m_world.Update(m_snake, m_textbox);
        ///////////////////////////////////////////

        m_elapsed -= sf::seconds(frametime);
    }
}
//////////////////  render  ////////////////////////
void Game::Render(){
    m_window.BeginDraw();   // clear

    //////// draw here  ///////
    
    m_snake.Render(*m_window.GetRenderWindow());
    m_world.Render(*m_window.GetRenderWindow());
    m_textbox.Render(*m_window.GetRenderWindow());
    ///////////////////////////

    m_window.EndDraw();     // display
}

//////////////////  handleinput //////////////////
void Game::HandleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDirection()!=Direction::Down){
        m_snake.SetDirection(Direction::Up);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDirection()!=Direction::Up){
        m_snake.SetDirection(Direction::Down);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDirection()!=Direction::Right){
        m_snake.SetDirection(Direction::Left);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDirection()!=Direction::Left){
        m_snake.SetDirection(Direction::Right);
    }
}
//////////////////  other  /////////////////////
Window* Game::GetWindow(){
    return &m_window;
}
//////////////////  clock  /////////////////////
void Game::RestartClock(){
    m_elapsed += m_clock.restart();
}