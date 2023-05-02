#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#pragma once

using MessageContainer = std::vector<std::string>;

class Textbox{

  public:
    Textbox();
    // 可见行数, 字符大小, 整个文本框的宽度，在屏幕上绘制文本的位置
    Textbox(int visible, int charSize, int width, sf::Vector2f screenPos); 
    ~Textbox();

    void Render(sf::RenderWindow& window);

    void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
    void Add(std::string message);
    void Clear();
  private:
    MessageContainer m_message;
    int m_numVisible;

    sf::RectangleShape m_backdrop;
    sf::Text m_content;
    sf::Font m_font;

};
//////////////////  构造 / 析构函数 //////////////////////
Textbox::Textbox(){
    Setup(5, 9, 200, sf::Vector2f(0, 0));
}
Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos){
    Setup(visible, charSize, width, screenPos);
}
Textbox::~Textbox(){
    Clear();
}
//////////////////// setup ///////////////////////
void Textbox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos){
    m_numVisible = visible;

    // 设置内容样式
    sf::Vector2f offset(2.0f, 2.0f);    // 偏差

    m_font.loadFromFile("arial.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(charSize);
    //m_content.setColor(sf::Color::Green);
    m_content.setPosition(screenPos + offset);

    // 设置背景样式
    m_backdrop.setSize(sf::Vector2f(width, (visible*(charSize * 1.2f))));
    m_backdrop.setFillColor(sf::Color(90,90,90,90));
    m_backdrop.setPosition(screenPos);
}
//////////////////// add clear //////////////////////
void Textbox::Add(std::string message){
    m_message.push_back(message);
    if(m_message.size() > m_numVisible){
        m_message.erase(m_message.begin());
    }
}
void Textbox::Clear(){
    m_message.clear();
}
//////////////////// render //////////////////////////
void Textbox::Render(sf::RenderWindow& window){
    std::string content;

    for(auto &it : m_message){
        content.append(it + "\n");
    }
    // 如果内容不为空
    if(content != ""){
        m_content.setString(content);
        window.draw(m_backdrop);
        window.draw(m_content);
    }
}