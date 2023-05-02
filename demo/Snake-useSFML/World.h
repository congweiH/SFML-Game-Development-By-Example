#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Textbox.h"

class World{

  public:
    World(sf::Vector2u worldSize);       // worldSize表示贪吃蛇运行范围的大小，有时候和窗口大小不一定相等
    ~World();

    // update and render
    void Update(Snake& palyer, Textbox& textbos);
    void Render(sf::RenderWindow& window);

public:
    // get set method
    int GetBlockSize();
private:
    void RespawnApple();    // 生成苹果


  private:
    int m_blockSize;        // 一个网格的大小
    sf::Vector2u m_worldSize; 

    sf::Vector2i m_applePosition;       // 苹果所在的位置
    sf::CircleShape m_appleShape;       // 渲染苹果

    sf::RectangleShape m_bounds[4];      // 边界

};
//////////////////  构造 / 析构函数  /////////////////
World::World(sf::Vector2u worldSize){
    // 设置时间种子
    srand(time(0));

    m_worldSize = worldSize;
    m_blockSize = 16;

    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize / 2);
    RespawnApple();
    
    // 设置边界的大小 和 放置的位置
    for(int i = 0; i < 4; ++i){
        m_bounds[i].setFillColor(sf::Color(150,0,0));
        if( i % 2 ){    // 1上 3下 边界
            m_bounds[i].setSize(sf::Vector2f(m_worldSize.x, m_blockSize));
        } else{         // 0左 2右 边界
            m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_worldSize.y));
        }
        if(i < 2){     // 0 是 左边界， 1 是 上边界
            m_bounds[i].setPosition(0,0);
        }else{         // 2 是 右边界，3 是下边界
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            m_bounds[i].setPosition(sf::Vector2f(m_worldSize));
        }
    }
}
World::~World() {  }
///////////////// RespawnApple  //////////////////
void World::RespawnApple(){
    int maxX = (m_worldSize.x / m_blockSize) - 2;   // 减去边界
    int maxY = (m_worldSize.y / m_blockSize) - 2;

    m_applePosition = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1); 
    m_appleShape.setPosition(m_applePosition.x * m_blockSize, m_applePosition.y * m_blockSize);
}
///////////////// update and render //////////////
void World::Update(Snake &player, Textbox &textbox){
    // 蛇吃到食物
    if(player.GetPosition() == m_applePosition){
        player.Extend();
        player.IncreseScore(10);
        textbox.Add("you eat an apple.score+10,score:" + std::to_string(player.GetScore()));
        RespawnApple();
    }

    // 检测蛇是否碰到边界
    if(player.GetPosition().x <= 0 || player.GetPosition().y <= 0 ||
        player.GetPosition().x >= m_worldSize.x/m_blockSize-1 || 
        player.GetPosition().y >= m_worldSize.y/m_blockSize-1){
            player.Lose(textbox);
        }
}
void World::Render(sf::RenderWindow& window){
    // 渲染苹果
    window.draw(m_appleShape);
    // 渲染边界
    for(int i = 0; i < 4; i++){
        window.draw(m_bounds[i]);
    }
}
/////////////////  get set method  /////////////////
int World::GetBlockSize(){
    return m_blockSize;
}
