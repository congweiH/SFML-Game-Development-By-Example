#include <iostream>
#include <SFML/Graphics.hpp>

class Window{
  public:
    Window();
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();

    void BeginDraw();   // clear window
    void Draw(sf::Drawable& drawable);     // render
    void EndDraw();     // display

    void Update();      // process events of window
    void ToggleFullscreen();    // press and full

    bool IsDone();      // window is closed or not
    bool IsFullscreen();    // fullscreen or not

    sf::Vector2u GetWindowSize();
    sf::RenderWindow *GetRenderWindow();

  private:
    void Setup(const std::string& title, const sf::Vector2u& size);
    void Create();      // create window
    void Destroy();     // destroy window

    sf::RenderWindow m_window;
    std::string m_windowTitle;
    sf::Vector2u m_windowSize;

    bool m_isDone;
    bool m_isFullscreen;
};
//////////////////// 构造 / 析构函数 /////////////////////
Window::Window(){
    Setup("Window", sf::Vector2u(640,480));
}
Window::Window(const std::string &title, const sf::Vector2u& size){
    Setup(title, size);
}
Window::~Window(){
    Destroy();
}

////////////////// setup、create、destroy /////////////////////
void Window::Setup(const std::string &title, const sf::Vector2u& size){
    m_windowTitle = title;
    m_windowSize = size;
    m_isDone = false;
    m_isFullscreen = false;

    Create();
}
void Window::Create(){
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}
void Window::Destroy(){
    m_window.close();
}

//////////////////////   update , ToggleFullscreen ////////////////////////
void Window::Update(){
    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_isDone = true;
        } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){
            ToggleFullscreen();
        }
    }
}
void Window::ToggleFullscreen(){
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}
/////////////////////   draw ///////////////////////////////
void Window::BeginDraw(){
    m_window.clear(sf::Color::Black);
}
void Window::Draw(sf::Drawable& drawable){
    m_window.draw(drawable);
}
void Window::EndDraw(){
    m_window.display();
}
/////////////////////  get set method ////////////////////////
bool Window::IsDone(){
    return m_isDone;
}
bool Window::IsFullscreen(){
    return m_isFullscreen;
}
sf::Vector2u Window::GetWindowSize(){
    return m_windowSize;
}
sf::RenderWindow *Window::GetRenderWindow(){
    return &m_window;  
}