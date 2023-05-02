#include <SFML/Graphics.hpp>
#include <vector>
#pragma once
#include "Textbox.h"

// 蛇的一节
struct SnakeSegment{
    SnakeSegment(int x, int y) : position(x, y){ }
    sf::Vector2i position;
};
using SnakeContainer = std::vector<SnakeSegment>;       // 重命名
// 方向枚举
enum class Direction{ None, Up, Down, Left, Right };
// 蛇类
class Snake{

  public:
    Snake(int blockSize);
    ~Snake();

    // update and render
    void Update(Textbox& textbox);      // 每帧执行一次
    void Render(sf::RenderWindow &window);  // 在窗口中渲染

  public:
    void Extend();      // 变长
    void Reset();       // 将蛇设置为初始状态
    void Lose(Textbox& textbox);        // 游戏失败处理的事情
    void IncreseScore(int score);

  public:
    // get set method
    void SetDirection(Direction dir);
    Direction GetDirection();
    Direction GetPhysicalDirection();   // 蛇的原始方向，用于修改bug
    int GetSpeed();
    sf::Vector2i GetPosition();
    int GetScore();

  private:
    void Move();                // 蛇移动
    void CheckCollision(Textbox& textbox);      // 检测自己和自己碰撞
    void Cut(int segments);     // 蛇撞到自己，在撞的地方切断      

  private:
    SnakeContainer m_snakebody;   // 蛇

    Direction m_dir;
    int m_speed;            // 蛇运行的速度
    int m_blockSize;       // 地图网格的大小
    int m_score;            // 分数

    sf::RectangleShape m_bodyRect;  // Shape used in rendering
};
////////////////////  构造 / 析构函数 //////////////////////
Snake::Snake(int blockSize){  
    m_blockSize = blockSize;
    m_bodyRect.setSize(sf::Vector2f(m_blockSize-1, m_blockSize-1)); // 渲染的时候比网格大小少1
    Reset();   
}
Snake::~Snake(){ }
//////////////////  Reset  //////////////////////
void Snake::Reset(){
    m_snakebody.clear();

    m_snakebody.push_back(SnakeSegment(7,7));
    m_snakebody.push_back(SnakeSegment(6,7));
    m_snakebody.push_back(SnakeSegment(5,7));

    m_dir = Direction::None;
    m_speed = 10;
    m_score = 0;
}
///////////////// move   ////////////////////
void Snake::Move(){
    for(int i = m_snakebody.size() - 1; i > 0; i--){
        m_snakebody[i].position = m_snakebody[i - 1].position;
    }
    if(m_dir == Direction::Left){
        -- m_snakebody[0].position.x;
    } else if(m_dir == Direction::Right){
        ++ m_snakebody[0].position.x;
    } else if(m_dir == Direction::Up){
        -- m_snakebody[0].position.y;
    } else if(m_dir == Direction::Down){
        ++ m_snakebody[0].position.y;
    }
}
///////////////// extend /////////////////////
void Snake::Extend(){
    if(m_snakebody.empty()) return;
    // 最后一节
    SnakeSegment& tail_head = m_snakebody[m_snakebody.size()-1];
    // 如果蛇只有一节
    if(m_snakebody.size() == 1){
        if(m_dir == Direction::Up){
            m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
        }else if(m_dir == Direction::Down){
            m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
        }else if(m_dir == Direction::Left){
            m_snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
        }else if(m_dir == Direction::Right){
            m_snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
        }
    }else{
        // 倒数第二节
        SnakeSegment& tail_bone = m_snakebody[m_snakebody.size() - 2];

        if(tail_head.position.x == tail_bone.position.x){

            if(tail_head.position.y > tail_bone.position.y){
                m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
            }else{
                m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
            }

        }else if(tail_head.position.y == tail_bone.position.y){
            
            if(tail_head.position.x > tail_bone.position.x){
                m_snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
            }else{
                m_snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
            }

        }

    }
}
///////////////// increscore /////////////////
void Snake::IncreseScore(int score){
    m_score += score;
}
/////////////////  checkcollision && cut //////////////
void Snake::CheckCollision(Textbox& textbox){
    if(m_snakebody.size() < 5) return;

    SnakeSegment& head = m_snakebody.front();
    for(auto it = m_snakebody.begin() + 1; it != m_snakebody.end(); it ++){
        if(it->position == head.position){
            int segments = m_snakebody.end() - it;
            Cut(segments);
            m_score -= segments * 10;;
            textbox.Add("you collide yourself.score-=" + std::to_string(segments * 10) + ".score:" + std::to_string(m_score));
            break;
        }
    }
}
void Snake::Cut(int segments){
    for(int i = 0; i < segments; i++){
        m_snakebody.pop_back();
    }
}
/////////////////  Lose   ////////////////////
void Snake::Lose(Textbox &textbox){
    // 失败之后重新开始
    textbox.Add("game over.your score:" + std::to_string(m_score));
    textbox.Add("game restart.your score:0");
    Reset();
}
///////////////// update and render ////////////////////
void Snake::Update(Textbox& textbox){
    if(m_snakebody.empty()) return;
    if(m_dir == Direction::None) return;
    Move();
    CheckCollision(textbox);
}
void Snake::Render(sf::RenderWindow& window){
    if(m_snakebody.empty()) return;

    // 渲染头
    auto head = m_snakebody.begin();
    m_bodyRect.setFillColor(sf::Color::Yellow);
    m_bodyRect.setPosition(head->position.x * m_blockSize, head->position.y * m_blockSize);
    window.draw(m_bodyRect);
    // 渲染尾
    m_bodyRect.setFillColor(sf::Color::Green);
    for(auto it = m_snakebody.begin() + 1; it != m_snakebody.end(); ++it){
        m_bodyRect.setPosition(it->position.x * m_blockSize, it->position.y * m_blockSize);
        window.draw(m_bodyRect);
    }
}
///////////////// get set method ///////////////////
void Snake::SetDirection(Direction dir){
    m_dir = dir;
}
Direction Snake::GetDirection(){
    return m_dir;
}
int Snake::GetSpeed(){
    return m_speed;
}
sf::Vector2i Snake::GetPosition(){
    if(m_snakebody.empty()) return sf::Vector2i(1,1);
    return m_snakebody[0].position;
}
Direction Snake::GetPhysicalDirection(){
    if(m_snakebody.size() <= 1){
        return Direction::None;
    }
    SnakeSegment& head = m_snakebody[0];
    SnakeSegment& neck = m_snakebody[1];
    if(head.position.x == neck.position.x){
        if(head.position.y > neck.position.y){
            return Direction::Down;
        }else{
            return Direction::Up;
        }
    }else if(head.position.y == neck.position.y){
        if(head.position.x > neck.position.x){
            return Direction::Right;
        }else{
            return Direction::Left;
        }
    }
    return Direction::None;
}
int Snake::GetScore(){
    return m_score;
}