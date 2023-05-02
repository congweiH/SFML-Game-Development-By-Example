
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <cstdlib>

enum class EventType{

    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo{
    EventInfo(){
        m_code = 0;
    }
    EventInfo(int event){
        m_code = event;
    }

    union{
        int m_code;
    };
    
};
using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails{
    EventDetails(const std::string& bindName) : m_name(bindName){
        Clear();
    }

    std::string m_name;
    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // Single key code.

    void Clear(){
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
};

struct Binding{
    Binding(const std::string& name) : m_name(name), m_details(name), c(0){

    }

    void BindEvent(EventType type, EventInfo info = EventInfo()){
        m_events.emplace_back(type, info);
    }

    Events m_events;
    std::string m_name;
    int c;
    EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

///////////////// event manager calss /////////////////////
class EventManager{
  public:
 	EventManager();
 	~EventManager();
 	bool AddBinding(Binding *binding);
 	bool RemoveBinding(std::string name);
    void SetFocus(const bool& focus);
    
    // Needs to be defined in the header!
 	template<class T>
 	bool AddCallback(const std::string& name, void(T::*func)(EventDetails*), T* instance){
 		auto temp = std::bind(func,instance, std::placeholders::_1);
 		return m_callbacks.emplace(name, temp).second;
 	}
 	void RemoveCallback(const std::string& name){
 		m_callbacks.erase(name);
 	}
 	void HandleEvent(sf::Event& event);
 	void Update();
 	sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr){
 		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
 	}
    
  private:
 	void LoadBindings();
 	Bindings m_bindings;
 	Callbacks m_callbacks;
 	bool m_hasFocus;
};
///////////////////  构造 / 析构函数 //////////////////////////////
EventManager::EventManager() : m_hasFocus(true) {
    LoadBindings();
}
EventManager::~EventManager(){
    for(auto &itr : m_bindings){
        delete itr.second;
        itr.second = nullptr;
    }
}
//////////////////////// add and remove///////////////////////
bool EventManager::AddBinding(Binding *binding){
    if(m_bindings.find(binding->m_name) != m_bindings.end()){
        return false;
    }
    return m_bindings.emplace(binding->m_name, binding).second;
}
bool EventManager::RemoveBinding(std::string name){
    auto itr = m_bindings.find(name);
    if(itr == m_bindings.end()){
        return false;
    }
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}
/////////////////////////// handle event ///////////////////////
void EventManager::HandleEvent(sf::Event &event){
    // Handling SFML events.
 	for (auto &b_itr : m_bindings){
 		Binding* bind = b_itr.second;
 		for (auto &e_itr : bind->m_events){
 			EventType sfmlEvent = (EventType)event.type;
 			if (e_itr.first != sfmlEvent){ continue; }
 			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
 				if (e_itr.second.m_code == event.key.code){
 					// Matching event/keystroke.
 					// Increase count.
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 					break;
 				}
 			} else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
                if (e_itr.second.m_code == event.mouseButton.button){
 					// Matching event/keystroke.
 					// Increase count.
 					bind->m_details.m_mouse.x = event.mouseButton.x;
 					bind->m_details.m_mouse.y = event.mouseButton.y;
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 					break;
 				}
 			} else {
 				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel){
 					bind->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
 				} else if (sfmlEvent == EventType::WindowResized){
 					bind->m_details.m_size.x = event.size.width;
 					bind->m_details.m_size.y = event.size.height;
 				} else if (sfmlEvent == EventType::TextEntered){
 					bind->m_details.m_textEntered = event.text.unicode;
 				}
 				++(bind->c);
 			}
 		}
 	}
}
////////////////////////  update  ///////////////////////
void EventManager::Update(){
    if(!m_hasFocus) { return; }
    for (auto &b_itr : m_bindings){
 		Binding* bind = b_itr.second;
 		for (auto &e_itr : bind->m_events){
 			switch (e_itr.first){
 			case(EventType::Keyboard) :
 				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))){
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 				}
 				break;
 			case(EventType::Mouse) :
 				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))){
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 				}
 				break;
 			case(EventType::Joystick) :
 				// Up for expansion.
 				break;
 			}
 		}
 		if (bind->m_events.size() == bind->c){
 			auto callItr = m_callbacks.find(bind->m_name);
 			if(callItr != m_callbacks.end()){
 				callItr->second(&bind->m_details);
 			}
 		}
 		bind->c = 0;
 		bind->m_details.Clear();
 	}
}
///////////////////////// loadbindings //////////////////
void EventManager::LoadBindings(){
	std::string delimiter = ":";
 	std::ifstream bindings;
 	bindings.open("keys.cfg");
 	if (!bindings.is_open()){
 		std::cout << "! Failed loading keys.cfg." << std::endl;
 		return; 
    }
 	std::string line;
 	while (std::getline(bindings, line)){
 		std::stringstream keystream(line);
 		std::string callbackName;
 		keystream >> callbackName;
 		Binding* bind = new Binding(callbackName);
 		while (!keystream.eof()){
 			std::string keyval;
 			keystream >> keyval;
 			int start = 0;
 			int end = keyval.find(delimiter);
 			if (end == std::string::npos){
 				delete bind;
 				bind = nullptr;
 				break;
 			}
 			EventType type = EventType(stoi(keyval.substr(start, end - start)));
 			int code = stoi(keyval.substr(end + delimiter.length(),keyval.find(delimiter, end + delimiter.length())));
 			EventInfo eventInfo;
 			eventInfo.m_code = code;
 			bind->BindEvent(type, eventInfo);
 		}
 		if (!AddBinding(bind)){ delete bind; }
 		bind = nullptr;
 	}
 	bindings.close();
}

void EventManager::SetFocus(const bool& focus){
    m_hasFocus = focus;
}