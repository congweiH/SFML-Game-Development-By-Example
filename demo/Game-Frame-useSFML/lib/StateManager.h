#include "BaseState.h"
#include "Window.h"
#include "EventManager.h"

enum class StateType{
    Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

struct SharedContext{
    SharedContext() : m_wind(nullptr), m_eventManager(nullptr){ }
    
    Window* m_wind;
    EventManager* m_eventManager;
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager{
  public:
	StateManager(SharedContext* shared);
 	~StateManager();

 	void Update(const sf::Time& time);
 	void Draw();

 	void ProcessRequests();

 	void SwitchTo(const StateType& type);
 	void Remove(const StateType& type);

    // get set method
    SharedContext* GetContext();
 	bool HasState(const StateType& type);
  private:
 	// Methods.
 	void CreateState(const StateType& type);
 	void RemoveState(const StateType& type);

 	template<class T>
 	void RegisterState(const StateType& type){
         m_stateFactory[type] = [this]() -> BaseState*{
             return new T(this);
         };
    }

 	// Members.
 	SharedContext* m_shared;
 	StateContainer m_states;
 	TypeContainer m_toRemove;
 	StateFactory m_stateFactory;
};

/////////////////// 构造 / 析构 /////////////////////
StateManager::StateManager(SharedContext* shared) : m_shared(shared){
    
}
StateManager::~StateManager(){
    for(auto &itr : m_states){
        itr.second -> OnDestroy();
        delete itr.second;
    }
}