# 译《SFML Game Development By Example》

## 0 序言 

本系列教程来源于《SFML Game Development By Example》一书

下面是正文

## 1 It's Alive! It's Alive! – Setup and First Program

### 1.1 Opening a window 

​		你可能知道，在屏幕上画东西需要一个窗口。幸运的是，SFML​ 允许我们轻松地打开和管理自己的窗口！让我们像往常一样，在项目中添加一个名为 main.cpp 的文件。这将是我们应用的入口点。基本应用程序的基本结构如下所示：

```c++
#include <SFML/Graphics.hpp>

int main(){
    
    return 0;
}
```

​		注意我们已经包含了 SFML​ 的 graphics 头文件。这将为我们提供打开一个窗口和绘制所需的一切。废话不多说，让我们看看打开一个窗口的代码：

```c++
#include <SFML/Graphics.hpp>

int main() {
    // create window
    sf::RenderWindow window(sf::VideoMode(640, 480), "First window!");

    // game loop
    while (window.isOpen()) {
        sf::Event event;
        // check events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window button clicked.
                window.close();
            }
        }
        // 清屏，用黑色填充
        window.clear(sf::Color::Black);

        // Draw here.

        // 展示画的内容
        window.display();
    }
    return 0;
}
```

> SFML 使用 sf 名称空间，因此必须在其数据类型、枚举和静态类成员前面加上“ sf:: ”		

​		我们在这里做的第一件事是声明并初始化  RenderWindow 类型的窗口实例。在本例中，我们使用了它的构造函数，但是也可以将其留空，然后通过传入完全相同的参数来使用它的 create 方法，其中最多可以取两个参数:  sf::videoMode​ 和一个 std::string 窗口标题。VideoMode 的构造函数接受两个参数: 窗口的宽度和高度。还有第三个可选参数，以每像素位为单位设置颜色深度。它的默认值是 32​ ，这对于我们的目的来说已经足够好的渲染了，所以我们现在不要为此而担忧。

​		在创建窗口实例之后，我们进入一个 while 循环，使用窗口方法之一 isOpen 检查它是否仍然打开。这有效地创造了我们的游戏循环，这是我们所有代码的核心部分。

​		让我们看看一款典型游戏的图表:

![image-20210116134912388](\img\1_1.png)

​		游戏循环的目的是检查事件和输入，在帧间更新我们的游戏世界（也就是移动玩家和敌人，检查变化等等）最后在屏幕上绘制一切。这个过程需要每秒重复多次，直到窗口关闭。次数的多少因应用程序而异，有时高达每秒数千次迭代。第二章（Give It Some Structure - Building the Game Framework）将涵盖管理和限制我们的应用程序的帧率，以及使游戏以恒定的速度运行。

​		大多数应用程序需要有一种方法来检查窗口是否已关闭、调整大小或移动。这就是事件处理的切入点。SFML提供了一个事件类，我们可以使用它来存储事件信息。在游戏循环的每次迭代中，我们需要利用窗口实例的pollEvent 方法检查发生的事件并处理它们。在本例中，我们只对鼠标单击关闭窗口按钮时被分派的事件感兴趣。我们可以检查 Event 类的公共成员类型是否匹配适当的枚举成员，在本例中是 sf::Event::Closed。如果是这样，我们可以调用窗口实例的close方法，程序将终止。

>事件必须在所有SFML应用程序中处理。如果没有事件循环轮询事件，窗口将变得无响应，因为它不仅向用户提供事件信息，而且还为窗口本身提供了一种处理其内部事件的方法，这对于窗口对移动或调整大小作出反应是必要的。

​		在完成所有这些之后，有必要从前一个迭代中清除窗口。如果不这样做，我们所利用的一切都会堆积起来，造成混乱。想象屏幕是一块白板，你想在别人已经在上面乱涂乱画的情况下在上面画些新东西。但是，我们不需要抓取橡皮擦，而是需要调用窗口实例的 clear 方法，该方法以 sf::Color 数据类型作为参数，如果没有提供参数，则默认为黑色。屏幕可以被清除为sf::Color类的静态成员提供的任意枚举颜色，也可以传递sf::Color的一个实例，该实例有一个构造函数，该构造函数为单个颜色通道接受无符号整数值:红色、绿色、蓝色，还有可选的alpha。后者为我们提供了一种明确指定所需范围颜色的方法，如下所示:

```c++
	window.clear(sf::Color(0,0,0,255))
```

​		最后，我们调用 window.display() 方法来显示所绘制的所有内容。这使用了一种被称为双缓冲的技术，这是现在游戏中的标准技术。基本上，任何绘制的东西都不会立即绘制在屏幕上，而是绘制到一个隐藏的缓冲区，一旦display被调用，然后复制到我们的窗口。双缓冲用于防止 graphical artifacts，如撕裂，这是由于显卡驱动程序从帧缓冲区拉出，而它仍在写入，导致部分绘制的图像显示。调用display方法是必须的，不可避免的，否则窗口将显示为一个静态的正方形，没有发生任何变化。

> 记住，在动态链接应用程序的情况下，将SFML库.dll文件包含在您的可执行文件依赖的同一目录中。

​		在编译和执行代码时，我们会发现自己有一个空白的控制台窗口，上面有一个640x480像素的黑色窗口，不到20行代码，还有一个打开的窗口。不是很令人兴奋，但还是比 E.T. for Atari 2600 好一点。我们在屏幕上画点东西吧!

### 1.2 Basics of SFML drawing

​		就像在幼儿园，我们将从基本形状开始，然后到更复杂的类型。让我们先声明并设置一个矩形来渲染它: ·

```c++
	sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(320,240);
```

​		sf::RectangleShape是sf::Shape的派生类，它继承了sf::Drawable，这是一个抽象基类，所有实体都必须继承并实现它的虚拟方法，以便能够在屏幕上绘制。它还继承了sf::Transformable，它提供了移动、缩放和旋转实体所需的所有功能。这种关系允许我们的矩形被转换，以及渲染到屏幕上。在它的构造函数中，我们引入了一个新的数据类型:sf::Vector2f。它本质上只是一个由两个浮点数x和y组成的结构体，它们代表二维空间中的一个点，不要与std::vector混淆，后者是一个数据容器。

> SFML为整数和无符号整数提供了其他一些向量类型:sf::Vector2i和sf::Vector2u。实际的sf::Vector2类是模板化的，所以任何原始数据类型都可以像这样使用它:
>
> ```c++
> 	sf::Vector2<long> m_vector
> ```

​		矩形构造函数接受 sf::Vector2f 单个参数，它表示矩形的大小，以像素为单位，是可选的。在第二行中，我们通过提供SFML预定义的颜色之一来设置矩形的填充颜色。最后，我们通过调用setPosition方法来设置形状的位置，并在x轴和y轴(在本例中是窗口的中心)传递它的位置。在我们画出矩形之前，还差一件事：

```c++
	window.draw(rectangle); // Render our shape.
```

​		这一行调用在window.display()之前，负责把我们的形状呈现在屏幕上。让我们运行修改后的应用程序，看看结果:

![image-20210116143338652](\img\1_2.png)

​		现在我们有一个红色的正方形画在屏幕上，但它不是很正中。这是因为任何sf::Transformable的默认原点(它只是一个表示对象全局位置的2D点)位于局部坐标(0,0)，即左上角。在本例中，该矩形的左上角被设置到屏幕中心的位置。这可以通过调用setOrigin方法并传入我们形状想要的代表新原点局部坐标来轻松解决，我们想要的新原点在正中间:

```c++
	rectangle.setOrigin(64.0f,64.0f);
```

​		如果形状的大小由于某种原因未知，矩形类提供了一个很好的方法getSize，它返回一个包含大小的float向量:

```c++
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
```

​		现在我们的形状高兴地坐在黑屏的正中央。让这一切成为可能的整个代码段看起来有点像这样:

```c++
#include <SFML/Graphics.hpp>

int main(){
	sf::RenderWindow window(sf::VideoMode(640,480),"Rendering the rectangle.");

    // Creating our shape.
	sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(320,240);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				// Close window button clicked.
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(rectangle); // Drawing our shape.
		window.display();
	}
}
```

### 1.3 Drawing images in SFML

​		为了在屏幕上绘制图像，我们需要熟悉两个类:sf::Texture和sf::Sprite。texture 本质上就是显卡上的图像，目的是让它快速绘制。任何给定的图片在你的硬盘驱动器可以变成一个 texture 加载它:

```c++
	sf::Texture texture;
	if(!texture.loadFromFile("filename.png"){
		// Handle an error.
	}
```

​		loadFromFile方法返回一个布尔值，这是处理加载错误的一种简单方法，比如找不到文件。如果你有一个控制台窗口和你的SFML窗口一起打开，你会注意到一些信息被打印出来，以防纹理加载失败: 

`Failed to load image "filename.png" . Reason : Unable to open file​`

> 除非在loadFromFile方法中指定了完整路径，否则它将被解释为相对于工作目录。需要注意的是，虽然工作目录通常与可执行文件本身启动时的目录相同，但在IDE中编译和运行应用程序(在我们的例子中是Microsoft Visual Studio)通常会将其设置为项目目录，而不是调试或发布文件夹。如果您提供了相对路径，请确保将您要加载的资源放在.vcxproj项目文件所在的同一目录中。

​		还可以从内存、自定义输入流或sf::Image实用工具类加载纹理，这些工具类帮助存储和操作原始像素的图像数据，这将在后面的章节中进行更广泛的讨论。

### 1.4 What is a sprite?

​		一个 sprite，就像我们到目前为止所使用的sf::Shape派生类一样（比如在这个例子中的sf::Texture），是一个sf::Drawable对象，也支持一系列的转换，包括物理的和图形的。把它想象成一个简单的矩形，加上一个纹理:

![image-20210116145737420](\img\1_3.png)

​		sprite 提供了在屏幕上渲染纹理或纹理的一部分的方法，以及转换纹理的方法，这使得精灵依赖于纹理的使用。sf::Texture 不是一个轻量级的对象, sf::Sprite 的出现是出于性能方面的原因，即使用它所绑定纹理的像素数据，这意味着只要精灵使用它所绑定的纹理，纹理就必须存在于内存中，并且只有当它不再被使用时才可以重新分配。在我们设置好纹理后，我们就很容易设置精灵并绘制它了:

```c++
	sf::Sprite sprite(texture);
	...
	window.draw(sprite);
```

​		通过引用将纹理传递给精灵构造函数是可选的。可以在任何时候通过setTexture方法更改它绑定的纹理:

```c++
	sprite.setTexture(texture);
```

​		因为像sf::Shape一样，sf::Sprite继承自sf::Transformable，所以我们可以使用相同的方法来操作和获取原点、位置、比例和旋转。

​		现在是时候应用我们到目前为止获得的所有知识，并编写一个利用这些知识的基本应用程序了:

```c++
int main(){
	sf::RenderWindow window(sf::VideoMode(640,480),"Bouncing mushroom.");

    sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("Mushroom.png");
	sf::Sprite mushroom(mushroomTexture);
	sf::Vector2u size = mushroomTexture.getSize();
	mushroom.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        if((mushroom.getPosition().x+(size.x/2) > window.getSize().x && increment.x > 0) 			|| (mushroom.getPosition().x - (size.x/2) < 0 && increment.x < 0)){
        // Reverse the direction on X axis.
            increment.x = -increment.x;
        }
        if((mushroom.getPosition().y+(size.y/2) > window.getSize().y && increment.y > 0) 			|| (mushroom.getPosition().y - (size.y / 2) < 0 && increment.y < 0)){
        // Reverse the direction on Y axis.
            increment.y = -increment.y;
        }
        mushroom.setPosition(mushroom.getPosition() + increment);
        window.clear(sf::Color(16,16,16,255)); // Dark gray.
        window.draw(mushroom); // Drawing our sprite.
        window.display();
	}
    return 0;
}
```

​		上面的代码将产生一个在窗口周围跳跃的精灵，每次它碰到窗口边界时都会反转方向。为了使代码更短，加载纹理的错误检查在这种情况下被省略。事件处理后的两个if语句部分在主循环负责检查我们的精灵和更新由加号或减号表示的增量值的方向，因为您只能在单个轴上走向正端或负端。记住，形状的原点默认是它的左上角，如下所示:

![image-20210116151529796](.\img\1_4.png)

​		正因为如此，我们必须在检查形状是否在底部或右侧出界时补偿整个宽度和高度，或者确保它的原点在中间。本例中，我们采用后一种方法，从蘑菇的位置增加或减少一半的纹理大小，以检查它是否仍然在我们想要的空间内。如果不是，只需在屏幕外的轴上反转增量浮点向量的符号，瞧！我们有跳跃！

![image-20210116151736145](\img\1_5.png)

​		此外，你可以随意使用sf::Sprite的setColor方法，它可以用想要的颜色为精灵着色，也可以通过调整sf:: color类型的第四个参数，它对应于alpha通道，使精灵变得透明:

```c++
	mushroom.setColor(sf::Color(255, 0, 0, 255)); // Red tint.
```

### 1.5 Common mistakes

​		通常，SFML的新用户会尝试这样做:

```c++
	sf::Sprite CreateSprite(std::string l_path){
		sf::Texture texture;
		texture.loadFromFile(l_path);
		. . .
		return sf::Sprite(texture);
	}
```

​		当试图绘制返回的精灵时，在精灵应该位于的地方会弹出一个白色方块。发生了什么？好吧，回头看看我们覆盖纹理的部分。只要它被精灵使用，它就需要在范围内，因为它存储了一个指向纹理实例的指针。从上面的例子中，我们可以看到它是静态分配的，所以当函数返回时，在堆栈上分配的纹理现在超出了作用域并弹出。噗。一去不复返了。现在精灵指向一个它不能使用的无效资源，并绘制了一个白色矩形。这并不是说你不能直接在堆上分配内存，而是通过进行一个新的调用，但这不是这个例子的重点。这里的要点是，对于任何应用程序，适当的资源管理都是至关重要的，因此要注意资源的生命周期。在第六章（Set It in Motion! – Animating and Moving around Your World）我们将介绍如何设计自己的资源管理器，并自动处理类似的情况。

​		另一个常见的错误是保留了太多的纹理实例。一个单一的纹理可以被任意多的精灵使用。sf::Texture并不是一个轻量级对象，所以我们可以使用相同的纹理来保存大量的sf::Sprite实例，并且仍然能够获得出色的性能。重新加载纹理对于显卡来说也是很昂贵的，所以如果你想让你的应用程序运行得更快，保持尽可能少的纹理。这就是使用 tile sheets 背后的想法，它只是一个大的纹理，里面有小的图像。这赋予了更好的性能，因为我们不需要保持几百个纹理实例并逐个加载文件，我们只需要加载一个纹理并通过指定读取区域来访问任何想要的贴图。这一点在以后的章节中也会得到更多的关注。

​		使用不支持的图像格式或格式选项是另一个相当常见的问题。最好是在官方网站上查询有关文件格式支持的最新信息。你可以在这里找到一个简短的列表: [https://www.sfml-dev.org/documentation/2.2/classsf_1_1Image.php#a9e4f2aa8e36d0cabde5ed5a4ef80290b](https://www.sfml-dev.org/documentation/2.2/classsf_1_1Image.php#a9e4f2aa8e36d0cabde5ed5a4ef80290b)

​		最后，LNK2019错误值得一提。无论指南、教程或书籍提到多少次如何正确地设置项目并将其链接到任何给定的库，都没有关系。在这个世界上没有什么是完美的，尤其是人。当试图编译你的项目时，你的IDE输出可能会被类似这样的消息淹没:

`error LNK2019: unresolved external  symbol. . .​`

​		不要惊慌，也请不要在论坛上发布几百行代码。您只是忘了在链接器输入中包含所有必需的附加依赖项。重新访问我们介绍的设置项目以使用SFML的部分，并确保所有内容都是正确的。另外，请记住，您需要包括其他库所依赖的库。例如，总是必须包含系统库，如果正在使用图形模块，则必须包含窗口库，等等。静态链接的库也需要链接它们的依赖项。

## 2 Give It Some Structure – Building the Game Framework
### 2.1 Graduating to ravioli

​		让我们从小事做起，每款游戏都需要有一个窗口，正如你在第1章中所知道的那样，它需要被创建、销毁，它的事件需要被处理。它还需要能够清除屏幕，并更新自己，以显示屏幕清除后绘制的任何东西。此外，跟踪窗口是否被关闭，是否处于全屏模式，以及拥有切换全屏模式的方法将非常有用。最后，我们当然需要绘制窗口。了解了所有这些，我们的窗口类的头文件将会像这样:

```c++
class Window {

  public:
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    void BeginDraw(); // Clear the window
    void EndDraw();   // Display the change

    void Update();

    bool IsDone();
    bool IsFullscreen();
    sf::Vector2u GetWindowSize();

    void ToggleFullscreen();

    void Draw(sf::Drawable &drawable);

  private:
    void Setup(const std::string &title, const sf::Vector2u &size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
};
```

​		因为我们想在内部处理窗口的设置，所以setup方法以及destroy和create方法都是私有的。可以将这些方法看作是这个类的用户不需要知道的辅助方法。在安装完成后保留一些信息是一个好主意，比如窗口大小或窗口上方显示的标题。最后，我们保留两个布尔变量来跟踪窗口的关闭情况和全屏状态。

> 在我们的窗口类中使用的命名约定称为匈牙利符号。当然，使用它并不是必需的，但在处理大量代码、试图追踪bug以及在更大的团队中工作时，它被证明是有用的。我们将在本书中使用它。更多有关资讯可在此浏览: [https://en.wikipedia.org/wiki/Hungarian_notation](https://en.wikipedia.org/wiki/Hungarian_notation)

### 2.2 Implementing the window class

​		现在我们有了我们的蓝图，让我们开始实际构建我们的窗口类。入口和出口似乎都是一个很好的起点:

```c++
	Window::Window(){ Setup("Window", sf::Vector2u(640,480)); }
	Window::Window(const std::string& title, const sf::Vector2u& size){
		Setup(title,size);
	}
	Window::~Window(){ Destroy(); }
```

​		构造函数和析构函数的实现都简单地利用了我们即将实现的辅助方法。还有一个默认构造函数，它不接受参数并初始化一些预先设置的默认值，这不是必需的，但很方便。说到这里，让我们来看看设置方法:

```c++
	void Window::Setup(const std::string& title,const sf::Vector2u& size){
		m_windowTitle = title;
		m_windowSize = size;
		m_isFullscreen = false;
		m_isDone = false;
		Create();
	}
```

​		再说一次，这很简单。如前所述，它初始化并跟踪一些将传递给构造函数的窗口属性。除此之外，它还调用了另一个名为Create的方法来进一步分解代码，这就是除了Destroy方法之外我们接下来要实现的:

```c++
	void Window::Create(){
		auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
		m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	}
```

```c++
	void Window::Destroy(){
		m_window.close();
	}
```

​		在这里，我们引入了SFML提供的一种新数据类型:sf::Uint32。它存储在style局部变量中，通过使用auto关键字自动推断该变量为所述类型。它只是一个无符号、固定大小的整数类型。在这个特定的例子中，我们使用32位整数，尽管SFML同时提供了8位、16位和32位的有符号和无符号类型。我们使用这个值来保存使用三元操作符的窗口的当前样式，并将其赋值为窗口样式枚举的默认或全屏样式。这是SFML中所有可能的窗口样式的完整列表:

|    枚举    |                    描述                    | 互相排斥 |
| :--------: | :----------------------------------------: | :------: |
|    None    |       没有边框或标题栏，最简约的风格       |    是    |
| Fullscreen |                  全屏模式                  |    是    |
|  Titlebar  |              标题栏和固定边框              |    否    |
|   Close    |            标题栏和一个关闭按钮            |    否    |
|   Resize   |  标题栏，可调整大小的边框和一个最大化按钮  |    否    |
|  Default   | 标题栏，可调整大小的边框，最大化和关闭按钮 |    否    |

​		互斥列仅表示所讨论的样式是否可以与其他样式一起使用。例如，可以使用c++中的按位或操作符将两种样式组合在一起，使窗口具有标题栏、可调整边框大小、最大化按钮和关闭按钮:

```c++
	auto style = sf::Style::Resize | sf::Style::Close;
```

​		但是，如果一个样式是互斥的，那么它就不能以这种方式与任何其他样式一起使用。

​		一旦我们有了自己的样式，除了使用统一初始化构造的sf::VideoMode类型之外，我们还可以简单地将它传递给窗口的create方法。就是这么简单。

​		我们窗口类的destroy方法将通过调用它的close方法来关闭窗口。这里需要注意的是，关闭的窗口将销毁其所有附加资源，但您仍然可以再次调用其create方法来重新创建窗口。如果窗口关闭，轮询事件和调用display方法仍然可以工作。它不会有任何效果。

​		让我们通过在适当的update方法中处理窗口事件来分解我们曾经坚实的代码块：

```c++
	void Window::Update(){
		sf::Event event;
		while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                m_isDone = true;
            } else if(event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F5){
                ToggleFullscreen();
            }
		}
	}
```

​		这和以前一样，我们只是处理事件。然而，与立即关闭窗口不同，我们只需将一直保留的布尔标志翻转过来，以检查窗口是否关闭:m_isDone。因为我们还对在全屏和正常窗口状态之间切换感兴趣，所以我们需要关注另一种类型的事件:sf:: event::KeyPressed。每当键盘键被按下时，这个事件就会被分派，它包含关于该键的信息存储在event.key结构体中。目前，我们只对被按下的键的代码感兴趣，然后我们可以根据sf::Keyboard枚举表检查该代码。在接收到F5键被按下的事件时，我们调用ToggleFullscreen方法，现在我们已经将代码分解为可管理的部分，实现起来相当简单:

```c++
	void Window::ToggleFullscreen(){
		m_isFullscreen = !m_isFullscreen;
		Destroy();
		Create();
	}
```

​		正如您所看到的，我们在这里做的唯一一件事是反转布尔类成员m_isFullscreen的值，它跟踪窗口状态。然后，我们需要销毁并重新创建窗口，以使其符合我们的更改。让我们来看看绘图方法:

```c++
	void Window::BeginDraw(){ m_window.clear(sf::Color::Black); }
	void Window::EndDraw(){ m_window.display(); }
```

​		这里没有引入任何新内容。我们只是在BeginDraw和EndDraw方法中包装了清除和显示的功能。剩下的就是简单的辅助方法了:

```c++
bool Window::IsDone(){ return m_isDone; }
bool Window::IsFullscreen(){ return m_isFullscreen; }
sf::Vector2u Window::GetWindowSize(){ return m_windowSize; }
```

```c++
void Window::Draw(sf::Drawable& drawable){
	m_window.draw(drawable);
}
```

​		这些基本方法提供了检索窗口信息的方法，而不需要对窗口类之外的任何东西进行过多的控制。现在，我们的window类就足够了。

### 2.3 Building the game class

​		我们在封装window类的基本功能方面做得很好，但这并不是需要重构的惟一代码块。在第一章，我们已经讨论了主要的游戏循环及其内容，主要是处理输入，更新游戏世界和玩家，最后是在屏幕上呈现所有内容。将所有功能都塞进游戏循环中通常只会产生意面式代码，因为我们想要摆脱这种情况，所以让我们考虑一种能够允许这种行为的更好结构:

```c++
#include "Game.h"

void main(int argc, void** argv[]){
	// Program entry point.
	Game game; // Creating our game object.
	while(!game.GetWindow()->IsDone()){
		// Game loop.
		game.HandleInput();
        game.Update();
		game.Render();
	}
}
```

​		上面的代码代表了main.cpp文件的全部内容，并完美地说明了如何使用一个结构合理的游戏类，它不会超出在一个无限循环中以正确的顺序调用正确的方法，直到窗口关闭。为了清晰起见，让我们来看看游戏类头部的简化版本:

```c++
class Game{
  public:
	Game();
	~Game();
	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();
	...
  private:
	void MoveMushroom();
	Window m_window;
	...
};
```

​		注意，game类保存了我们窗口的一个实例。可以用不同的方式来做，但对于我们目前的需要，这是绰绰有余的。

### 2.4 Putting our code to work

​		我们现在准备重新实现第1章的弹跳蘑菇演示。鉴于它是如此简单，我们将带领您完成将以前编写的代码适应于我们的新结构的整个过程。让我们开始设置我们的窗口和图形，我们将使用:

```c++
    Game::Game(): m_window("Chapter 2", sf::Vector2u(800,600)){
        // Setting up class members.
        m_mushroomTexture.loadFromFile("Mushroom.png");
        m_mushroom.setTexture(m_mushroomTexture);
        m_increment = sf::Vector2i(4,4);
    }
```

​		因为我们没有什么要清理的，所以我们的游戏析构函数现在仍然是空的:

```c++
	Game::~Game(){}
```

​		在这个例子中，我们不需要检查输入，所以让我们暂时不去管那个方法。然而，我们将要做的是在每一帧中更新精灵的位置:

```c++
void Game::Update(){
	m_window.Update(); // Update window events.
	MoveMushroom();
}
void Game::MoveMushroom(){
    sf::Vector2u windSize = m_window.GetWindowSize();
    sf::Vector2u textSize = m_mushroomTexture.getSize();

    if((m_mushroom.getPosition().x > windSize.x - textSize.x && m_increment.x> 0) ||
        (m_mushroom.getPosition().x < 0 && m_increment.x< 0)){
        m_increment.x = -m_increment.x;
    }
    if((m_mushroom.getPosition().y > windSize.y - textSize.y && m_increment.y> 0) ||
    (m_mushroom.getPosition().y < 0 &&m_increment.y< 0)){
    	m_increment.y = -m_increment.y;
    }
    
    m_mushroom.setPosition(m_mushroom.getPosition().x + m_increment.x,
    						m_mushroom.getPosition().y + m_increment.y);
}
```

​		实际上，您可能会注意到的第一件事是窗口类的update方法调用。我们已经讨论了SFML中事件处理的重要性，但仍然有必要再次注意这一点。剩下的代码基本上是一样的，除了我们现在有一个独立的方法负责更新蘑菇精灵的位置。剩下的代码基本上是一样的，除了我们现在有一个独立的方法负责更新蘑菇精灵的位置。现在是时候将精灵绘制到屏幕上了:

```c++
	void Game::Render(){
		m_window.BeginDraw(); // Clear.
        m_window.Draw(m_mushroom);
		m_window.EndDraw(); // Display.
	}
```

​		同样，代码相当直接。我们的窗口类完成了所有的工作，我们需要做的就是调用Draw方法，并在包装器方法之间传入sf::Drawable，以清除屏幕并显示更改。

​		把所有东西放在一起运行，应该会产生我们在第一章中看到的弹跳蘑菇。然而，你可能已经注意到，精灵的移动会根据你的电脑的繁忙程度而有所不同。从这个观察中我们可以学到关于游戏开发的一个重要教训。

### 2.5 Hardware and execution time

​		举了一个例子......

​		虽然这是最极端的例子，但速度管理是当今任何必须以恒定速度运行的软件的重要组成部分。除了硬件和架构的不同选择之外，您的软件可能运行得更快或更慢，这取决于您的系统当时的繁忙程度，或者在呈现图像之前代码需要完成的每个迭代的不同任务。考虑下面的例子:

![image-20210116165256590](F:\MyDataBase\articles\SFML教程\img\2_1.png)

​		左侧和右侧的变化都发生在1秒的间隔内。这两种情况下的代码完全相同。唯一的区别是主循环在该时间间隔内设法完成的迭代次数。可以预见的是，较慢的硬件将花费更长的时间来执行你的代码，因此将产生更少的迭代，从而导致精灵在1秒的时间间隔内移动次数更少，最终看起来就像左边一样。作为一名游戏开发者，确保你的产品在指定的规范指导下在所有系统上运行是非常重要的。这就是SFML时间管理的作用所在。

### 2.6 Controlling the frame-rate

​		SFML提供了一种为应用程序设置帧速率上限的方法。它是sf::RenderWindow类中的一个方法，恰当地称为setFramerateLimit：

```c++
	m_window.setFramerateLimit(60); // 60 FPS cap.
```

​		虽然这个特性不是绝对可靠的，但它确保了应用程序的帧率以合理的精度限制在提供的最大值，只要提供的上限不太高。记住，限制帧率也减少了程序的总体CPU消耗，因为它不再需要多次更新和重新绘制相同的场景。然而，对于速度较慢的硬件来说，这确实带来了一个问题。如果帧率低于所提供的值，模拟也会运行得更慢。设限只能解决一半的问题。让我们来看一些更实际的东西。进入 sf::Clock !

### 2.7 Using the SFML clock

​		sf::Clock类非常简单和轻量级，所以它只有两个方法:getElapsedTime()和restart()。它的唯一目的是用操作系统能够提供的最精确的方式测量从时钟的最后一个实例重新启动或创建以来所经过的时间。当使用getElapsedTime方法检索经过的时间时，它返回类型sf::Time。这背后的主要原因是额外的抽象层提供了灵活性，并避免强加任何固定的数据类型。sf::Time类也是轻量级的，它提供了三个有用的方法来将运行时间转换为秒，秒返回一个浮点值，毫秒返回一个32位整数值，微秒返回一个64位整数值，如下所示:

```c++
	sf::Clock clock;
	...
	sf::Time time = clock.getElapsedTime();

	float seconds = time.asSeconds();
	sf::Int32 milliseconds = time.asMilliseconds();
	sf::Int64 microseconds = time.asMicroseconds();
	...
	time = clock.restart();
```

​		如您所见，restart方法还返回sf::Time值。这样做是为了避免在调用restart方法之前调用getElapsedTime，并避免在这两个调用之间有一段时间，否则这段时间将无法解释。这对我们有什么用?我们处理的问题是相同的代码在其他平台上以不同的方式运行，因为我们无法解释它们的速度。我们使用以下代码在屏幕上移动精灵:

```c++
m_mushroom.setPosition(m_mushroom.getPosition().x + m_increment.x,
						m_mushroom.getPosition().y + m_increment.y);
```

​		这里使用的m_increment向量假设迭代之间的时间是常数，但这显然是不正确的。回想一下速度、时间和距离公式的神奇三角形:

![image-20210116170828615](\img\2_2.png)

​		要找到精灵在两次更新之间应该移动的距离，可以先定义它移动的设定速度。这里的时间值只是指程序完成整个循环所需的时间。为了准确测量，我们将调整 Game 类来使用sf::Clock :

```c++
class Game{
  public:
	...
	sf::Time GetElapsed();
	void RestartClock();
  private:
	...
    sf::Clock m_clock;
	sf::Time m_elapsed;
	...
};
```

​		我们添加的两个新的公共方法可以这样实现:

```c++
	sf::Time Game::GetElapsed(){ return m_elapsed; }
	void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
```

​		一旦完成这一任务，你便需要真正利用这一功能并在每次迭代后重新启动游戏时钟。这可以通过在所有工作完成后调用RestartClock方法在主游戏循环中实现:

```c++
    while(!game.GetWindow()->IsDone()){
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock(); // Restarting our clock.
    }
```

​		循环的最后一行将确保游戏类的m_elapsed成员将始终拥有在前一次迭代中所经过的时间值，所以让我们使用这些时间并确定我们的精灵应该移动多远:

```c++
float fElapsed = m_elapsed.asSeconds();

m_mushroom.setPosition(m_mushroom.getPosition().x + (m_increment.x * fElapsed),
						m_mushroom.getPosition().y + (m_increment.y * fElapsed));
```

​		我们现在使用m_increment作为速度的变量，而不是距离。通过在构造函数中查看前面的代码，我们将m_increment向量的x值和y值都设置为4。因为我们用秒来表示流逝时间，这基本上就像是说精灵需要每秒移动4个像素。这真的很慢，所以让我们换一种更刺激的方式:

```c++
Game::Game(){
	...
	m_increment = sf::Vector2i(400,400); // 400px a second.
}
```

​		编译和运行项目后，你应该会看到我们的精灵愉快地在屏幕上跳跃。现在它将在每台执行它的机器上移动相同的距离，无论帧率有多不稳定。此外，你可以使用SFML提供的sf::sleep功能来人为地放慢游戏循环，就像这样:

```c++
    while(!game.GetWindow()->IsDone()){
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
        sf::sleep(sf::seconds(0.2)); // Sleep for 0.2 seconds.
        game.RestartClock();
    }
```

​		您可以随意调整传递给sleep函数的参数。你会注意到它将精灵移动到相同的距离，无论每次迭代需要多长时间才能完成。

### 2.8 Fixed time-step

​		在某些情况下，我们编写的时间管理代码并不能真正正确地应用。假设我们只想以每秒60次的固定速率调用某些方法。它可以是只需要更新一定次数的物理系统，或者如果游戏是基于网格的，它就很有用。无论如何，当更新率非常重要时，固定的时间步长便是你的好友。与可变时间步不同的是，固定时间步方法将确保特定的游戏逻辑只在给定的速率下发生。实现一个固定的时间步非常简单。首先，我们必须确保不是覆盖前一个迭代所消耗的时间值，而是像这样添加到它上面:

```c++
void Game::RestartClock(){
	m_elapsed += m_clock.restart();
}
```

​		计算1秒间隔内单个更新所需时间的基本表达式如下所示:

![image-20210116172124986](\img\2_3.png)

​		假设我们希望游戏每秒更新60次。为了找到帧时间，我们将1除以60并检查所经过的时间是否超过了这个值，如下所示:

```c++
	float frametime = 1.0f / 60.0f;
	if(m_elapsed.asSeconds() >= frametime){
		// Do something 60 times a second.
		...
		m_elapsed -= sf::seconds(frametime); // Subtracting.
	}
```

​		注意最后的减法。这就是我们重置循环并保持模拟以恒定速度运行的方法。根据您的应用程序，您可能希望在更新之间让它 sleep，以减少CPU占用。除了这些细节，这些是固定时间步长的基本框架。这正是我们将在下一章完成的游戏中所使用的技术。

### 2.9 Common mistakes

​		在使用时钟时，SFML新手往往会把时钟放在错误的地方，并在错误的时间重新启动时钟。这样的事情最多只能导致“古怪”的行为。

> 请记住，每一行不是空的或被注释掉的代码都需要时间来执行。根据正在调用的函数或正在构造的类的实现方式，时间值可能从很小到无穷大不等。

​		像更新世界中的所有游戏实体、执行计算和渲染等都是非常昂贵的计算，所以请确保不要将这些调用排除在你的时间度量范围之外。总是要确保在主游戏循环结束之前，重新启动时钟并获取所经过的时间是你要做的最后一件事。

​		另一个错误是将时钟对象置于错误的范围内。考虑一下这个例子:

```c++
	void Game::SomeMethod(){
		sf::Clock clock;
		...
		sf::Time time = clock.getElapsedTime();
	}
```

​		假设这段代码的目的是测量sf::Clock对象启动后的时间以外的任何东西，那么这段代码将产生错误的结果。创建一个时钟实例只是测量它在其范围内存在的时间，而不是其他任何东西。这就是为什么game类中的时钟被声明为类成员的原因。因为时钟是在堆栈上创建的，所以只要上面的方法结束，时钟就会再次被销毁。

​		在float数据类型或sf:: time以外的任何其他数据类型中保存运行时间通常也是不允许的。像这样的事情并不是正确使用SFML的好例子:

```c++
class Game{
	...
	private:
	...
	float m_elapsed;
	...
};
```

​		尽管它可以工作，但这并不是完全的类型安全。在此过程中还需要更多的类型转换，因为您必须在每次时钟重新启动时调用这三个转换方法中的一个。再多钉一个钉子就能封住棺材了。SFML提供自己的时间类是有原因和方便的，所以除非有很好的理由不使用它，否则请避免使用任何其他数据类型。

​		由于我们在讨论时间，最后值得一提的一件事是c++中的控制台输出。虽然偶尔打印一些内容是可以的，即使只是为了调试目的，但不断的控制台垃圾邮件会减慢应用程序的速度。控制台输出本身非常慢，不能期望以与程序其余部分完全相同的速度执行。例如，在主游戏循环的每次迭代中打印内容将极大地降低应用程序的速度。

## 3 Get Your Hands Dirty – What You Need to Know
### 3.1 Game design decisions

​		某些版本的snake运行方式不同。然而，为了向经典方法致敬，我们将实现一条基于网格移动的蛇，如下图所示:

![image-20210116191857305](\img\3_1.png)

​		采用这种方法可以更容易地检查蛇部分和苹果之间的碰撞。网格移动基本上意味着以静态速率更新。这可以通过使用固定的时间步长来实现，我们在前面第二章已经介绍过了。外围区域代表着游戏的边界，在基于网格的移动中，这个范围是[1;Width-1]和[1;Height-1]。如果蛇头不在这个范围内，那就可以说玩家撞到墙上了。这里所有的网格段都是16px * 16px的;然而，这在任何时候都可以调整。除非玩家用光了生命值，否则我们希望在蛇的头部与身体发生碰撞时在交叉点切断蛇，减少剩下的生命值。这为游戏增加了些许多样性，同时又不会太不平衡。

​		最后，你可能已经注意到我们在这款游戏中使用了非常简单的图像呈现蛇的样子。这样做主要是为了保持事情的简单，以及添加一个经典的魅力到混合。使用精灵并不是一件非常复杂的事情，但是，我们先不要担心这个问题。

### 3.2 Implementing the snake structure

​		现在让我们创建将要使用的两个文件:Snake.h和Snake.cpp。在实际开发snake类之前，需要先定义一些数据类型和结构。我们可以从定义吃苹果的蛇的结构开始，就在蛇头文件中:

```c++
	struct SnakeSegment{
		SnakeSegment(int x, int y) : position(x,y){}
		sf::Vector2i position;
	};
```

​		可以看出，这是一个包含单个成员的非常简单的结构，该成员是一个整数向量，表示网格上的段的位置。这里的构造函数是用来通过初始化列表设置段的位置的。

> 在继续之前，请确保您能够使用标准模板库及其提供的数据容器。我们将专门使用std::vector来满足我们的需求。

​		我们现在已经定义了段类型，所以让我们开始实际地将snake存储在某个地方。对于初学者来说，std::vector会做得很好！在进行深入讨论之前，这里有一个简单的小技巧，用于治疗我们的“long-line-itus”代码。

```c++
	using SnakeContainer = std::vector<SnakeSegment>;
```

​		从C/ c++背景中您应该已经知道，using是一个整洁的小关键字，它允许用户为已知的数据类型定义别名。通过使用我们干净的新定义和auto关键字，我们可以防止以下情况的发生:

```c++
	std::vector<SnakeSegment>::iterator someIterator = ...
```

​		这是一个简单的方便问题，完全可以选择使用，然而，我们将在本书中一直装备这个有用的工具。

​		在真正开始使用snake类之前，我们需要定义的最后一种类型是方向枚举:

```c++
	enum class Direction{ None, Up, Down, Left, Right };
```

​		再说一遍，没什么特别的。蛇有四个方向可以移动。我们也有可能它静止不动，在这种情况下，我们可以把方向设为NONE。

### 3.3 The snake class

​		在设计任何物体之前，人们必须问自己它需要什么。在我们的例子中，蛇需要有一个移动的方向。它还需要有生命，记录分数，速度，是否丢失。最后，我们将存储一个矩形形状，它将代表蛇的每个部分。当所有这些都被寻址后，snake类的头文件看起来就像下面这样:

```c++
class Snake{
  public:
	Snake(int l_blockSize);
	~Snake();
	// Helper methods.
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();
	void Lose(); // Handle losing here.
	void ToggleLost();
	void Extend(); // Grow the snake.
	void Reset(); // Reset to starting position.
	void Move(); // Movement method.
	void Tick(); // Update method.
	void Cut(int l_segments); // Method for cutting snake.
	void Render(sf::RenderWindow& l_window);
  private:
	void CheckCollision(); // Checking for collisions.
	SnakeContainer m_snakeBody; // Segment vector.
	int m_size; // Size of the graphics.
	Direction m_dir; // Current direction.
	int m_speed; // Speed of the snake.
	int m_lives; // Lives.
	int m_score; // Score.
	bool m_lost; // Losing state.
	sf::RectangleShape m_bodyRect; // Shape used in rendering.
};
```

​		注意，我们正在为snake segment vector使用我们的新类型别名。这看起来还不太有用，但很快就会有用了。

​		如您所见，我们的类定义了一些方法，这些方法被设计用来分割功能，如Lose()、Extend()、Reset()和CheckCollision()。这将提高代码的可重用性和可读性。让我们开始实际实现这些方法:

```c++
Snake::Snake(int l_blockSize){
	m_size = l_blockSize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset();
}
Snake::~Snake(){}
```

​		构造函数非常简单。它有一个参数，也就是图形的大小。该值将被存储以供以后使用，类型sf::RectangleShape的成员将根据该值调整其大小。从大小上减去一个像素是一种非常简单的方法，保持蛇的部分看起来稍微分离，如下所示:

![image-20210118193601250](\img\3_2.png)

​		构造函数还在最后一行调用Reset()方法。头文件中的注释指出，该方法负责将snake移动到起始位置。让我们实现这一点:

```c++
void Snake::Reset(){
	m_snakeBody.clear();
	m_snakeBody.push_back(SnakeSegment(5,7));
	m_snakeBody.push_back(SnakeSegment(5,6));
	m_snakeBody.push_back(SnakeSegment(5,5));
	SetDirection(Direction::None); // Start off still.
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}
```

​		这段代码将在每次新游戏开始时被调用。首先，它将清除前一款游戏中的snake片段向量。在那之后，一些蛇片段将被添加。由于我们的实现，vector中的第一个元素总是头元素。为了保持简单，snake部分的坐标目前是硬编码的。

​		现在我们有了一条three-piece的蛇。我们现在要做的第一件事是将它的方向设为None。在玩家按下键移动蛇之前，我们不希望它移动。接下来，我们为速度、生命值和起始分数设置一些任意值。这些可以在以后根据你的喜好进行调整。我们还将m_lost标志设置为false，以表示发生了新一轮。

​		在继续更困难的方法实现之前，让我们快速覆盖所有的辅助方法:

```c++
void Snake::SetDirection(Direction l_dir){ m_dir = l_dir; }
Direction Snake::GetDirection(){ return m_dir; }
int Snake::GetSpeed(){ return m_speed; }

sf::Vector2i Snake::GetPosition(){
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1,1));
}
int Snake::GetLives(){ return m_lives; }
int Snake::GetScore(){ return m_score; }

void Snake::IncreaseScore(){ m_score += 10; }
bool Snake::HasLost(){ return m_lost; }
void Snake::Lose(){ m_lost = true; }
void Snake::ToggleLost(){ m_lost = !m_lost; }
```

​		这些方法相当简单。有描述性的名字很有帮助。现在让我们看看Extend方法:

```c++
void Snake::Extend(){
	if (m_snakeBody.empty()){ return; }
	
    SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
	
    if(m_snakeBody.size() > 1){
		SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
    	if(tail_head.position.x == tail_bone.position.x){
			if(tail_head.position.y > tail_bone.position.y){
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			} else {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		} else if(tail_head.position.y == tail_bone.position.y){	
			if(tail_head.position.x > tail_bone.position.x){
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			} else {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	} else {		// 蛇只有一节
		if(m_dir == Direction::Up){
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		} else if (m_dir == Direction::Down){
            m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		} else if (m_dir == Direction::Left){
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		} else if (m_dir == Direction::Right){
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}
```

​		当蛇碰到苹果的时候，正是这个方法让它长出来的。我们做的第一件事是创建一个segment vector中的最后一个元素的引用，称为tail_head。接下来我们有一个相当大的if-else语句块代码，两种情况都需要访问最后一个元素，所以现在创建引用是一个好主意，以防止重复代码。

> vector容器重载方括号操作符，以支持通过数字索引进行随机访问。它类似于数组，因此可以通过使用size() - 1的索引来引用最后一个元素。无论容器中元素的数量是多少，随机访问速度都是恒定的，这使得std::vector成为这个项目的良好选择。

​		本质上，这可以归结为两种情况:要么是蛇的长度超过了一段，要么不是。如果它确实有多个元素，则创建另一个称为tail_bone的引用，它指向最后一个元素的下一个元素。这是需要的以确定一个新的蛇块应该放置在延伸它，我们检查的方式是通过比较tail_head和tail_bone的position.x和position.y。如果x值相同，那么可以肯定地说这两部分在y轴上的差异，反之亦然。考虑下面的示例，其中橙色矩形是tail_bone，红色矩形是tail_head：

![image-20210119141704025](\img\3_3.png)

​		让我们分析面朝左边的例子：tail_bone 和 tail_head 有相同的 y 值，tail_head 的 x 值比 tail_bone 大，因此，下一个片段将被添加到与tail_head相同的坐标，除了x值将增加1。因为snakessegment构造函数可以方便地重载以接受坐标，所以很容易在将段推到向量后面的同时执行这个简单的数学运算。

​		在vector中只有一段的情况下，我们只需检查蛇的方向，并执行与之前相同的数学运算，只是这一次是基于头部面向的方向。前面的插图也适用于此，其中橙色矩形是头部，红色矩形是即将被添加的部分。如果它是面向左边的，我们增加x坐标1，同时保持y不变。如果x是朝右的，就可以减去x，以此类推。花点时间分析这幅图，并将它与前面的代码相关联。

​		当然，如果我们的蛇不动，这些都不重要。这正是update方法正在处理的内容，在我们的固定时间步长的例子中，它被称为“tick”:

```c++
void Snake::Tick(){
	if (m_snakeBody.empty()){ return; }
	if (m_dir == Direction::None){ return; }
	Move();
	CheckCollision();
}
```

​		方法的前两行是根据蛇的大小和方向来检查它是否应该移动。如前所述，Direction::None值是专门用来保持它不动的。蛇的移动完全包含在移动方法中:

```c++
void Snake::Move(){
	for (int i = m_snakeBody.size() - 1; i > 0; --i){
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}
	if (m_dir == Direction::Left){
		--m_snakeBody[0].position.x;
	} else if (m_dir == Direction::Right){
		++m_snakeBody[0].position.x;
	} else if (m_dir == Direction::Up){
		--m_snakeBody[0].position.y;
	} else if (m_dir == Direction::Down){
		++m_snakeBody[0].position.y;	
	}
}
```

​		我们从向后遍历vector开始。这样做是为了达到挪动的效果。我们也可以在不反向迭代矢量的情况下做到这一点，但是，这样做的目的是简单，让玩家更容易理解游戏的运作方式。出于同样的原因，我们再次使用随机访问操作符来使用数值索引，而不是vector迭代器。考虑下面的例子:

![image-20210119143457156](\img\3_4.png)

​		在我们调用tick方法之前，我们在它们的位置上有一组片段，这可以被称为“开始状态”。当我们开始向后迭代我们的向量时，我们从段#3开始。在for循环中，我们检查索引是否等于0，以确定当前段是否在snake的前面。在本例中，它不是，所以我们将段#3的位置设置为与段#2相同。前面的插图显示了这幅作品，在某种程度上，处于两个位置之间，这样做的目的只是为了能同时看到它们。实际上，分段3正好位于分段2的上方。

​		在同样的过程应用到蛇的第二部分之后，我们移动到它的头部。在这一点上，我们只需要让它在与它面向的方向相对应的轴上穿过一个空间。同样的思想也适用于这里，就像之前的例子一样，只是符号颠倒了。因为在我们的例子中，蛇是面向右的，所以它被移动到坐标(x+1;y)。一旦完成，我们就成功地将蛇移动了一格。

​		tick做的最后一件事是调用CheckCollision()方法。让我们来看看它的实现:

```c++
void Snake::CheckCollision(){
	if (m_snakeBody.size() < 5){ return; }

    SnakeSegment& head = m_snakeBody.front();
	for(auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr){
		if(itr->position == head.position){
			int segments = m_snakeBody.end() - itr;
			Cut(segments);
			break;
		}
	}
}
```

​		首先，没有必要检查碰撞，除非我们有超过四个片段。理解游戏的某些场景并进行检查以避免浪费资源是游戏开发的重要组成部分。如果我们的蛇有超过4个部分，我们将再次创建一个指向头部的引用，因为在任何情况下碰撞，这是第一个会碰撞到另一个部分的部分。没有必要检查所有部件之间的碰撞两次。我们还跳过了蛇头的迭代，因为显然不需要检查它是否与自身发生碰撞。

​		在这个基于网格的游戏中，我们检查碰撞的基本方法是将头部的位置与迭代器所表示的当前段的位置进行比较。如果两个位置相同，头部与身体相交。我们的解决方法在本章的“Game design decisions ”节中进行了简要介绍。必须在碰撞点切断蛇，直到玩家耗尽生命。为此，我们首先获取一个段计数的整数值，该数值介于被击中的段和结束的段之间。STL的迭代器相当灵活，因为使用vector的内存都是连续排列的，所以只需从vector中的最后一个元素减去当前的迭代器就可以得到这个值。这样做是为了知道有多少元素需要从蛇的后面移除，直到交叉点。然后我们调用负责切割蛇的方法。此外，由于一次只能有一个碰撞，我们打破for循环以避免浪费更多的时钟周期。

​		让我们来看看切割方法:

```c++
void Snake::Cut(int segments){
	for (int i = 0; i < segments; ++i){
		m_snakeBody.pop_back();
	}
	--m_lives;
	if (!m_lives){ Lose(); return; }
}
```

​		此时，只需根据segments值循环一定次数，然后从vector的后面取出元素即可。这有效地刺穿了蛇。其余的代码只是减少剩余生命的数量，检查它是否为零，如果没有更多的生命，则调用Lose()方法。

​		唷!这是相当多的代码。然而，还有一件事仍然存在，那就是把我们的方蛇呈现在屏幕上:

```c++
void Snake::Render(sf::RenderWindow& window){
	if (m_snakeBody.empty()){ return; }
	
    auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	window.draw(m_bodyRect);
	m_bodyRect.setFillColor(sf::Color::Green);
	for(auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr){
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		window.draw(m_bodyRect);
	}
}
```

​		与我们在这里实现的许多方法非常相似，我们需要遍历每个段。为了避免不必要的检查，头部被画在了循环的外面。我们将图形化表示蛇形部分的sf:: rectanglesshape的位置设置为其网格位置乘以m_size值，以便获得屏幕上的像素坐标。绘制矩形是实现snake类的最后一步!

### 3.4 The World class

​		我们的蛇现在可以移动和碰撞自己。虽然功能强大，但这并不能创造出真正令人兴奋的游戏。让我们给它一些界限和一些东西来咀嚼，通过介绍World 类来提高分数。

​		虽然可以为我们在这里讨论的所有内容创建单独的对象，但这个项目非常简单，可以将自身的某些方面很好地包含在一个类中，这个类可以很好地管理它们，而不会有太多麻烦。这个类负责保持游戏边界，以及维护玩家想要占领的苹果。

​		让我们来看看类头文件:

```c++
class World{
  public:
	World(sf::Vector2u windSize);
	~World();
	int GetBlockSize();
	void RespawnApple();		// 生成苹果
	void Update(Snake& player);
	void Render(sf::RenderWindow& window);
  
  private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;		// 跟踪苹果坐标
	int m_blockSize;			
	sf::CircleShape m_appleShape;	// 苹果形状
	sf::RectangleShape m_bounds[4];	// 边界
};
```

​		正如你在前面的代码中看到的，这个类还会跟踪游戏中的对象有多大。除此之外，它只保留四个矩形用于边界图形，一个圆用于绘制苹果，以及一个整数向量用于跟踪苹果的坐标，该向量名为m_item。让我们开始实现构造函数:

```c++
World::World(sf::Vector2u windSize){
	m_blockSize = 16;
	m_windowSize = windSize;
	RespawnApple();
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);
	for(int i = 0; i < 4; ++i){
		m_bounds[i].setFillColor(sf::Color(150,0,0));
		if(!((i + 1) % 2)){
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		} else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
        if(i < 2){
			m_bounds[i].setPosition(0,0);
		} else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}
World::~World(){}
```

​		在出现复杂的查找循环之前，我们只需从本地构造函数变量初始化一些成员值，设置苹果圆的颜色和半径，并调用RespawnApple()方法将其放置在网格的某个位置。

​		第一个for循环只针对游戏屏幕的四个边迭代4次，以便在每个边设置红色矩形墙。它为矩形填充设置一个深红色，并继续检查索引值。首先，用下面的表达式检查下标是偶数还是奇数: if(!((i + 1) % 2)){... 。这样做是为了知道每个壁在一个特定的轴上有多大。因为它必须与屏幕的其中一个尺寸一样大，我们只需将另一个尺寸与屏幕上的所有其他图形一样大，它由m_blockSize值表示。

​		最后一个if语句检查索引是否低于2。如果是，我们将处理左上角，因此我们只需将矩形的位置设置为(0,0)。由于SFML中所有基于矩形的绘图的原点总是左上角，因此在本例中我们不需要担心这个问题。然而，如果索引值为2或更高，我们将原点设置为矩形的大小，这有效地使其成为右下角。然后，我们将矩形的位置设置为与屏幕大小相同，这将把矩形一直放置到右下角。您可以简单地手动设置所有坐标和原点，但是这种方法使基本特性的初始化更加自动化。现在可能很难看到它的用途，但在更复杂的项目中，这种想法将会派上用场，所以为什么不现在就开始呢?

​		既然我们有了自己的围墙，让我们来看看如何让苹果重生:

```c++
void World::RespawnApple(){
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	
    m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}
```

​		我们必须做的第一件事是确定苹果可以产生的界限。为此，我们定义了两个值:maxX和max。这些设置为窗口大小除以块大小，这给了我们网格中的空格数，然后我们必须从中减去2。这是因为网格索引从0开始，而不是1，并且因为我们不想在右边或底部墙壁中生成苹果。由于苹果的坐标现在是可用的，我们可以通过将网格坐标乘以所有图形的大小来设置m_applshape图形的像素坐标位置。

​		让我们通过实现更新方法来实现所有这些特性:

```C++
void World::Update(Snake& player){
	if(player.GetPosition() == m_item){
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}
	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;
	if(player.GetPosition().x <= 0 || player.GetPosition().y <= 0 ||
	player.GetPosition().x >= gridSize_x – 1 || player.GetPosition().y >= gridSize_y - 1)	{
		player.Lose();
	}
}
```

​		首先，我们检查玩家的位置是否与苹果的位置相同。如果是，我们就会发生碰撞，蛇就会延伸，分数就会增加，苹果就会重生。接下来，我们决定网格大小，并检查玩家坐标是否在指定边界之外的任何地方。如果是这种情况，我们就调用Lose()方法来说明与墙壁的碰撞，并让玩家“game over”。

​		为了不让玩家感到盲目，我们必须展示游戏的边界以及主要兴趣点-苹果。 让我们在屏幕上绘制所有内容：

```c++
	void World::Render(sf::RenderWindow& window){
 		for(int i = 0; i < 4; ++i){
 			window.draw(m_bounds[i]);
 		}
 		window.draw(m_appleShape);
	}
```

​		我们要做的就是迭代四次并分别绘制四个边界。 然后我们画苹果，这表明我们对这种方法的兴趣。

​		还有一点要指出的是，其他类可能需要知道图形的大小，因此，让我们实现一个简单的方法来获取该值:

```c++
	int World::GetBlockSize(){ return m_blockSize; }
```

​		World 类到此结束。

### 3.5 Time to integrate

​		就像没有人使用的锤子是无用的一样，我们的两个类也没有被Game类所采用。.由于我们编写所有这些代码并不只是为了练习打字，所以让我们把所有的部分放在一起。首先，我们实际上需要向Game类添加两个新成员，您可能已经猜到了它们是什么：

```c++
class Game{
	...
  private:
	...
  	World m_world;
 	Snake m_snake;
};
```

​		接下来，让我们初始化这些成员。因为它们都有接受实参的构造函数，现在是初始化列表的时候了：

```c++
Game::Game(): m_window("Snake", sf::Vector2u(800, 600)),
 m_snake(m_world.GetBlockSize()),m_world(sf::Vector2u(800,600))
{
 	...
}
```

​		接下来，我们需要处理一些输入。正如你可能在前面的章节中回忆的那样，使用事件来实时输入确实是延迟的，并且不应该用于其他任何事情，除了检查不敏感的按键。幸运的是，SFML通过sf:: keyboard类提供了获取键盘实时状态的手段。它只包含静态函数，并不意味着需要初始化。其中一个功能正是我们在这里所需要的:isKeyPressed(sf::Keyboard::Key)。它接受的唯一参数是您想要检查其状态的实际键，它可以通过使用sf::Keyboard:: key枚举获得，如下所示:

```c++
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && m_snake.GetDirection() != Direction::Down){
        m_snake.SetDirection(Direction::Up);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
     && m_snake.GetDirection() != Direction::Up){
     	m_snake.SetDirection(Direction::Down);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
     && m_snake.GetDirection() != Direction::Right){
     	m_snake.SetDirection(Direction::Left);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
     && m_snake.GetDirection() != Direction::Left){
     	m_snake.SetDirection(Direction::Right);
    }
```

​		我们不想让蛇走与当前方向相反的方向。在任何给定的时间，它应该只有三个方向可以进入，使用GetDirection()方法确保我们不会反向发送蛇，本质上是吃掉它自己。如果我们有合适的输入和当前方向的组合，那么使用SetDirection()方法来调整它的方向是安全的。

​		让我们通过更新这两个类来使事情继续下去:

```c++
void Game::Update(){
	...
 	float timestep = 1.0f / m_snake.GetSpeed();
 	if(m_elapsed >= timestep){
 		m_snake.Tick();
 		m_world.Update(m_snake);
 		m_elapsed -= timestep;
 		if(m_snake.HasLost()){
       		m_snake.Reset();
 		}
 	}
	...
}
```

​		如前所述，我们在这里使用固定的时间步长，它包含了蛇的速度，以便更新每秒适当的次数。这也是我们检查玩家是否输了游戏并重新设置蛇的地方。

​		我们现在真的很接近了。是时候在屏幕上绘制所有东西了:

```c++
void Game::Render(){
 	m_window.BeginDraw();
 	// Render here.
 	m_world.Render(*m_window.GetRenderWindow());
 	m_snake.Render(*m_window.GetRenderWindow());
 	m_window.EndDraw();
}
```

​		和前面很像，我们只是调用两个类的渲染方法，并传入sf::RenderWindow的引用。这样我们的游戏才真正具有可玩性! 在成功编译和执行我们的项目后，我们应该得到如下图所示的结果:

![3_5](\img\3_5.png)

​		蛇一开始会保持静止，直到按下四个方向键中的一个。一旦它开始移动，它将能够吃掉苹果并成长一段，与自己的尾巴发生碰撞并在死亡前失去尾巴两次，如果玩家撞到墙上，它便会结束游戏。我们的游戏的核心版本完成了!因为你刚刚创造了自己的第一款游戏。

### 3.6 Hunting bugs

​		就像你对你的第一个项目感到骄傲和满意一样，没有什么是完美的。如果你真的花了一些时间玩这款游戏，你可能会注意到在快速按压按键时出现的奇怪事件，如下图所示:

![3_6](\img\3_6.png)

​		该图像表示两个连续更新之间的差异。似乎之前它面朝右然后面朝左，尾巴不见了。发生了什么事?在继续之前，尝试着自己去弄清楚它，因为它完美地说明了修复游戏缺陷的经验。

​		对它进行更多的研究，揭示了缩小问题范围的某些细节。让我们来分析一下当玩家开始快速敲击按键时会发生什么:

- 蛇是面向右的。
- 除左键或右键外的任何箭头键被按下。
- 蛇的方向被设定为另一个方向，比如说向上。
- 在游戏有机会更新之前按下右键。
- 由于snake的方向不再设置为右或左，输入处理程序中的if语句得到满足，并将方向设置为左。
- 游戏更新了蛇，并将其向左移动了一个空间。它的头和尾巴相撞，被砍了下来。

​		是的，似乎我们的方向检查是有缺陷的，并导致了这个错误。再一次，在继续前进之前，花点时间想办法解决这个问题。

### 3.7 Fixing bugs

​		让我们来讨论一下在这种情况下可能使用的几种方法。首先，程序员可能会考虑在某个地方放置一个标记，以记住当前迭代的方向是否已经设置，并在之后重新设置。这可以防止我们遇到的漏洞，但也可以锁定玩家与蛇互动的次数。假设它每秒移动一次。这意味着，如果你在一开始按下一个键，你将无法改变主意，并快速按下另一个键来纠正你的错误决定。

​		另一种方法可能是在对该迭代进行任何更改之前跟踪原始方向。然后，一旦update方法被调用，我们就可以在进行任何更改之前检查原始方向是否与我们收到的最新方向相反。如果是，我们可以简单地忽略它，并在做出任何更改之前将蛇移动到该方向。这将修复bug，不会给我们提供一个新的，但它会跟踪一个新的变量，可能会让人感到困惑。想象一下，在未来，您遇到了一个类似的bug，或者一个特性请求，需要您在这个变量之上跟踪另一个变量。想象这种事再发生一次，然后再发生一次。很快，您的检查语句可能看起来像这样:

```c++
if(var1 != something && var2 == something && var3 == true && var4 == !var3 ...)
```

​		这就是我们所说的混乱。最重要的是，想象你必须在四种不同的情况下检查相同的变量四次。很快就会发现，这是一个糟糕的设计，任何人都不应该使用它来向他人展示自己的代码。

​		你也许会问我们怎样才能纠正我们的问题。好吧，我们不能简单地依赖于使用snake类中的变量来确定它的方向，而是实现一个方法来查看它的结构并吐出它所面对的方向，如下所示:

```c++
Direction Snake::GetPhysicalDirection(){
	if(m_snakeBody.size() <= 1){
 		return Direction::None;
 	}
 	SnakeSegment& head = m_snakeBody[0];
 	SnakeSegment& neck = m_snakeBody[1];
 	if(head.position.x == neck.position.x){
 		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
 	} else if(head.position.y == neck.position.y){
 		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
 	}
 	return Direction::None;
}
```

​		首先，我们检查蛇的长度是否小于1节;在这种情况下，它朝哪个方向是无关紧要的因为如果它只有头，它就不会吃掉自己，如果矢量中没有段，它甚至不会有方向。假设它的长度超过了一段，我们得到了两个参考:头部和颈部，这是蛇头部之后的第二部分。然后，在实现snake类时，我们简单地检查它们的位置，并使用相同的逻辑来确定蛇面对的方向，如下图所示:

![3_7](\img\3_7.png)

​		这将返回一个正确的方向，除非蛇移动，否则不会改变，所以让我们调整输入处理代码来适应这些变化:

```c++
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDirection() != Direction::Down){
 	m_snake.SetDirection(Direction::Up);
}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDirection() != Direction::Up{
 	m_snake.SetDirection(Direction::Down);
}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDirection() != Direction::Right){
 	m_snake.SetDirection(Direction::Left);
} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
 && m_snake.GetPhysicalDirection() != Direction::Left){
 	m_snake.SetDirection(Direction::Right);
}
```

​		瞧!不会再让我们的蛇翻出来了。

​		游戏中还有一个错误没有被故意解决。试着找到它并修正它，以便在将来练习解决这类问题。

> 提示:这与游戏开始时蛇有多少段有关。

​		如果您想公平地完成这一工作，请尽量不要引用本书附带的已完成项目的代码，因为它已经被修复了。

### 3.8 Going the extra mile

​		功能性游戏还远不是完全完成的产品。当然，我们在一开始就拥有了所有我们想要的东西，但它仍然留有一些需要改进的地方，如记录分数和显示我们拥有多少条生命。首先，您的主要本能可能是在屏幕上的某个地方添加一些文本，简单地打印出您还剩下多少条生命。您甚至可能想要在控制台窗口中简单地将它打印出来。如果是这样的话，这部分的目的是通过介绍我们将在本书过程中使用和改进的东西来改变你的思维方式: Textbox。

​		如果这个名字对您来说没有任何意义，那么简单地想象一下，在任何给定的通信应用程序(如MSN Messenger或Skype)上都有一个聊天窗口。每当新消息被添加时，它就会随着旧消息的上移而被添加到底部。该窗口保存了一次可见的特定数量的消息。这不仅适用于游戏打印休闲消息的目的，也可以用于调试。让我们像往常一样，从写头文件开始:

```c++
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
```

​		我们首先为所有消息的容器定义数据类型。在本例中，我们再次使用std::vector，因为这是目前更熟悉的选择。为了使它看起来更好，可读性更好，我们添加了一个矩形形状作为类的成员之一，它将被用作背景。在此之上，我们引入了一种新的数据类型:sf::Text。这是一种可绘制的类型，表示任何类型化字符或字符字符串，可以调整大小、字体和颜色，也可以进行转换，就像SFML中的任何其他绘制类型一样。

​		让我们开始实现我们的新功能:

```c++
Textbox::Textbox(){
    Setup(5, 9, 200, sf::Vector2f(0, 0));
}
Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos){
    Setup(visible, charSize, width, screenPos);
}
Textbox::~Textbox(){
    Clear();
}
```

​		如您所见，它有两个构造函数，其中一个可以用来初始化一些默认值，另一个允许通过传入一些值作为参数进行定制。后面是字符大小(以像素为单位)、整个文本框的宽度(以像素为单位)和表示应该在屏幕上绘制文本的位置的浮动向量。这些构造函数所做的就是调用Setup方法并将所有这些参数传递给它，所以让我们来看看它:

```c++
void Textbox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos){
    m_numVisible = visible;

    // 设置内容样式
    sf::Vector2f offset(2.0f, 2.0f);    // 偏差

    m_font.loadFromFile("arial.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(charSize);
    m_content.setColor(sf::Color::Green);
    m_content.setPosition(screenPos + offset);

    // 设置背景样式
    m_backdrop.setSize(sf::Vector2f(width, (visible*(charSize * 1.2f))));
    m_backdrop.setFillColor(sf::Color(90,90,90,90));
    m_backdrop.setPosition(screenPos);
}
```

​		除了初始化其成员值之外，该方法还定义了一个偏移float向量，用于适当地分隔文本，并从左上角提供一些填充。它还通过以下方法来设置我们的sf::Text成员:首先创建绑定到它的字体，将初始字符串设置为空，设置字符大小和颜色，并将其在屏幕上的位置设置为提供的position参数，并考虑适当的偏移量。此外,它设置背景的大小通过使用提供的宽度和可见的行数乘以乘法的结果的字符大小和一个常数浮点值为1.2,为了占行之间的间距。

> 有时，我们只需要简单地玩一下代码，看看什么才是真正有效的。找到在所有情况下都能工作的特定数字常量是一种情况，在这种情况下，为了确定正确的值，只需进行测试。不要害怕尝试新事物，看看什么有效。

​		因为我们使用vector来存储消息，所以添加一个新的或全部删除消息就像使用push_back和clear方法一样简单：

```c++
void Textbox::Add(std::string l_message){
	 m_messages.push_back(l_message);
 	if(m_messages.size() < 6){ return; }
 	m_messages.erase(m_messages.begin());
}
void Textbox::Clear(){ m_messages.clear(); }
```

​		在添加新消息的情况下，检查我们是否有比我们看到的更多的消息将是一个好主意。在周围放置我们不会看到或不再需要的东西是一种浪费，因此第一个在那时绝对看不到的消息将从消息容器中删除。

​		我们已经非常接近完成这个巧妙的功能了。现在唯一剩下的事情就是绘制它，这总是由Render方法负责。

```c++
void Textbox::Render(sf::RenderWindow& wind){
 	std::string content;
 	for(auto &itr : m_messages){
 		content.append(itr+"\n");
 	}
 	if(content != ""){
 		m_content.setString(content);
 		wind.draw(m_backdrop);
 		wind.draw(m_content);
 	}
}
```

​		代码以设置std::string开始，以在屏幕上保存所有可见消息。然后，只需循环遍历消息向量并将每个消息的文本添加到我们的本地std::string变量中，并在末尾添加一个新的行符号即可。最后，在检查局部变量并确保它不是空的之后，我们必须设置sf::Text类型的m_content成员来保存我们推送消息的字符串，并在屏幕上绘制背景和文本。这就是Textbox类的全部内容。

​		在我们的游戏类中添加了一个Textbox实例作为成员后，我们可以开始设置它:

```c++
Game::Game() ... {
	...
 	m_textbox.Setup(5,14,350,sf::Vector2f(225,0));
	...
 	m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
}
```

​		将一些常量值传递给m_textbox成员的Setup方法后，我们立即在构造函数中开始使用它，实际输出第一个消息。让我们通过最后一次调整Game::Render()方法来完成整合:

```c++
void Game::Render(){
 	m_window.BeginDraw();
 	// Render here.
 	m_world.Render(*m_window.GetRenderWindow());
 	m_snake.Render(*m_window.GetRenderWindow());
 	m_textbox.Render(*m_window.GetRenderWindow());
 	m_window.EndDraw();
}
```

​		它与我们之前实现的两个类都一样，除了文本框现在是我们绘制的最后一个东西，这意味着它将显示在其他所有东西之上。在将更多信息添加到游戏中并编译我们的项目后，我们最终应该得到如下内容:

![3_8](\img\3_8.png)

​		这个文本框，以其最基本的形式，是我们将在本书中涵盖的贪吃蛇游戏的最后一个新增内容。你可以随意使用它，看看你还能想出什么东西来为游戏增添趣味!

### 3.9 Common mistakes

​		下面这句话是人们经常忘记的:

```c++
	srand(time(nullptr));
```

​		如果你注意到，每次你启动游戏时所生成的数字都是完全相同的，那么可能是因为你没有为随机数生成器播下种子，或者你没有提供合适的种子。建议始终使用unix时间戳，如所示。

> 这个特定随机函数的使用应该被限制在与安全性和密码学无关的情况下。由于引入的偏差，将它与模算子结合使用可以产生令人难以置信的不均匀结果。

​		另一个相当常见的问题是程序员选择数据容器来保存它们的结构。让我们举个例子:

```c++
	using SnakeContainer = std::vector<SnakeSegment>;
```

​		这定义了我们的snakcontainer的类型。如果您已经编译了我们编写的代码，您会注意到它运行得相当流畅。现在考虑下一行代码:

```c++
	using SnakeContainer = std::deque<SnakeSegment>;
```

​		由于这两个容器在STL中实现的方式，我们的代码中没有其他更改，所以可以随意尝试将您的snakcontainer的数据类型从std::vector更改为std::deque。编译并运行项目之后，您肯定会对性能有所提高。为什么会这样?嗯，尽管std::vector和std::deque基本上可以以相同的方式使用，但它们本质上是不同的。vector保证其元素在内存中是连续的，而双端队列则不然。根据大多数插入和删除操作是在哪里进行的，性能也存在差异。如果您不确定要使用哪个容器，请确保自己查找或对其进行基准测试。永远不要盲目地假设，除非性能不是您关心的主要问题。

​		最后，更开放的一点是，不要害怕摆弄、修改、更改、修改或改变你看到的任何代码片段。你可能犯的最大的错误就是没有从破坏和修复中学习。将我们编写的代码仅仅看作是正确方向上的推送，而不是特定的配方。如果更好地理解一件事意味着你必须先打破它，那就这么做吧。

# 4 Grab That Joystick – Input and Event Management

## 4.1 Retrieving peripheral input

​		前面的几章已经稍微涉及了检索外围输出的主题，而且具有讽刺意味的是，已经涵盖了整个类的范围。简单回顾一下，sf::Keyboard是一个类，它提供一个静态方法isKeyPressed(sf::Keyboard::Key)来确定某个键盘键的实时状态，该方法作为参数传递给方法，由sf::Keyboard::Key枚举表表示。因为这个方法是静态的，所以sf::Keyboard不需要实例化，可以如下方式使用：

```c++
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
 		// Do something if the W key is pressed.
	}
```

​		这是我们在前几章中检查输入的方法，然而，如果我们想要检查更多的击键，它确实会导致相当多的if/else语句混乱。

## 4.2 Checking for mouse input

​		不出所料，SFML还提供了一个类似于sf::Keyboard的类，该类的思路与获取鼠标:sf:: Mouse的实时状态相同。就像它的伙伴键盘一样，它提供了一种检查鼠标按钮是否被按下的方法，如下所示：

```c++
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
 		// Do something if the left mouse button is pressed.
	}
```

​		sf::Mouse类在任何给定的鼠标上提供它自己的可能按钮枚举，我们总共有5个鼠标：

| sf::Mouse::Left     | The left mouse button     |
| ------------------- | ------------------------- |
| sf::Mouse::Right    | The right mouse button    |
| sf::Mouse::Middle   | Mouse wheel being clicked |
| sf::Mouse::XButton1 | First extra mouse button  |
| sf::Mouse::XButton2 | Second extra mouse button |

​		除此之外，sf::Mouse类还提供了一种获取和设置当前鼠标位置的方法:

```c++
// Getting the mouse position.
sf::Vector2i mousePos = sf::Mouse::getPosition(); // 1
sf::Vector2i mousePos = sf::Mouse::getPosition(m_window); // 2
// Setting the mouse position.
sf::Mouse::setPosition(sf::Vector2i(0,0)); // 3
sf::Mouse::setPosition(sf::Vector2i(0,0),m_window); // 4
```

​		这两个方法都有重载版本，接受对窗口的引用，以确定是查看相对于窗口还是相对于桌面的鼠标坐标。考虑下面的示例：

![4_1](\img\4_1.png)

​		如果没有提供对窗口的引用，就像前面例子中的第1行，返回的鼠标位置是从桌面原点到鼠标所在点的距离。但是，如果提供了对窗口的引用，那么位置就是窗口原点和鼠标位置之间的距离。换句话说，示例#2中的鼠标位置是相对于窗口的。同样的逻辑也适用于第3行和第4行，只是鼠标的位置被设置为提供的int向量参数。

## 4.3 Plug in your controller

​		是的，正如标题所述，SFML不仅支持来自键盘和鼠标的输入，还支持来自您可能已连接到计算机的额外外设的输入。通过使用类sf::Joystick(它只包含静态方法，就像前两个类一样)，可以检查控制器是否连接，检查其按钮状态，甚至确定沿着特定轴的位置(如果控制器支持的话)。

​		SFML支持最多8个不同的控制器同时连接，由范围为[0;7]的数值索引来识别。正因为如此，sf::Joystick提供的每个方法都必须至少有一个参数，即控制器ID。首先，让我们看看一种确定控制器是否连接的方法:

```c++
    if (sf::Joystick::isConnected(0)){
        // We have a controller with an id 0.
    }
```

​		如果我们有一个ID为0的控制器，我们可以检查它实际上支持多少个按钮，如下所示:

```c++
	unsigned int n_buttons = sf::Joystick::getButtonCount(0);
```

​		因为没有其他方法可以抽象地定义这个星球上的每个控制器的按钮，所以它们只是由0到31之间的数字索引来引用。可以通过调用isButtonPressed()方法来检查按钮是否按下，如下所示:

```c++
    if(sf::Joystick::isButtonPressed(0,1)){
        // Button 1 on controller 0 is pressed.
    }
```

​		为了检查控制器是否支持特定的轴，我们可以使用hasAxis()方法:

```c++
    if(sf::Joystick::hasAxis(0,sf::Joystick::X)){
        // Controller 0 supports movement on X axis.
    }
```

​		sf::Joystick::Axis枚举封装了控制器可以支持的所有坐标轴，所以可以像前面的代码中所示的那样进行检查。在控制器支持的情况下，可以通过如下方法获取其当前沿轴的位置：

```c++
    float p_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float p_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    // Do something with p_x and p_y.
```

​		上述方法将返回控制器0上X轴和Y轴的当前位置。

> 因为sf::Joystick状态在检查事件时更新，所以在事件有机会被轮询之前使用这些方法可能会出现一些问题。如果是这样的话，最好手动调用sf::Joystick:Update()方法，以确保你拥有周边设备的最新状态。

## 4.4 Understanding the sf::Event

​		再次强调，sf::Event是我们简要提及的内容，但是，如果我们希望构建一个能够无缝处理所有类型的事件而不出现任何问题的系统，那么在继续之前，有必要对它进行扩展并更好地理解它。首先，让我们重申一下什么是event。 sf::Event 是一个union, 在c++术语意味着它是一个特殊的类只可容纳一个非静态数据成员,它有好几个,比如KeyEvent,拥有一个键盘事件的信息,SizeEvent,它保存了关于被调整的窗口大小的信息，以及其他许多信息。由于sf::Event的这种性质，如果新来者以错误的方式处理事件，比如在sf::Event中访问KeyEvent结构体(当它不是活动数据成员时)，这可能是一个陷阱。由于union的所有成员共享相同的内存空间，这将导致未定义的行为，并将导致应用程序崩溃，除非您知道自己在做什么。

​		让我们来看看处理事件的最基本方式:

```c++
sf::Event event;
while(m_window.pollEvent(event)){
 	switch(event.type){
 	case sf::Event::Closed:
 		m_window.close();
 		break;
 	case sf::Event::KeyPressed:
 		if(event.key.code == sf::Keyboard::W){
 			// Do something when W key gets pressed once.
 		}
 		break;
 	}
}
```

​		没有我们之前没见过的东西，尽管我们要填补空白，知道到底发生了什么，这很重要。首先，命名为event的sf::Event实例由pollEvent()方法填充。根据它的类型，它将选择union中的一个结构作为活动结构，以携带与事件相关的数据。然后，我们可以检查事件的类型，它是由sf:: event:: type枚举表定义的，并确保我们使用了正确的数据成员来获取所需的信息。如前所述，尝试访问event.key。例如，事件类型为sf:: event::Closed的代码将导致未定义的行为。

> 记住，**使用sf::Event::KeyPressed 事件来进行实时角色移动是一个糟糕的主意**。在应用一个小的延迟之前，这个事件只被分派一次，然后它再次被分派。这里考虑一个文档编辑器。当你按下一个键并按住它时，一开始它只显示一个字符，然后才会写更多的字符。这和这个事件的运作方式完全一样。将它用于任何需要在键被按住时保持连续的操作都不是最优的，**应该用sf::Keyboard::isKeyPressed()来替换**，以便检查键的实际状态。同样的想法也适用于鼠标和控制器输入。对于每次击键只需要发生一次的事情，使用这些事件是非常理想的。

​		虽然这种方法在小型项目中是可管理的，与之前的输入示例几乎相同，但在更大规模的情况下，它可能很快就会失控。让我们面对现实吧，以我们在前一个项目中所做的方式处理所有事件、击键和每个输入设备的状态是一场噩梦。还不相信吗?假设有一个应用程序，您想要检查多个键同时被按下，并在它们被按下时调用某个函数。不太糟糕?好吧，那我们就把事件也算进去吧。为了调用函数，您需要检查是否同时按下了两个键和发生了某个事件。这又增加了一层复杂性，但没有什么是您无法处理的，对吗?。在那里添加一些布尔标记来跟踪事件状态或击键应该不会太难。

​		一段时间过去了，现在应用程序需要支持从文件中加载组合键，以便使您的方法更加动态和可定制。你手上有一堆烂摊子。你可以构建它，但要添加新功能或扩展堆积如山的废话会很尴尬，你很可能会举手投降。为什么让自己通过这一切,当只有一些努力和用白板描述你可以想出一个自动化的方法,将不需要旗帜,是灵活的,可以加载任何组合键和事件从一个文件,并且仍然保持代码一样整洁,如果不是更多吗?让我们通过在一个能够处理所有这些难题的系统上工作来智能地解决这个问题。

## 4.5 Introducing the event manager

​		弄清楚我们想从应用程序中得到什么是设计过程的第一个也是最关键的部分。有时很难覆盖所有的基础，但是忘记一个可能会改变所有代码的结构方式的特性，然后再尝试实现它，可能会对您投入到软件中的所有工作造成严重的破坏。说到这里，让我们列出一个列表，列出我们希望事件管理器具有的特性：

- 能够将任意组合的键、按钮或事件(从现在起称为绑定)与由字符串标识的所需功能结合起来
- 将上述功能绑定到方法，如果满足绑定的所有条件(例如，按下一个键、单击鼠标左键或窗口失去焦点)，就会调用这些方法
- 一种事件管理器可以处理正在轮询的实际SFML事件的方法
- 从配置文件加载绑定

​        我们有我们的规格，现在让我们开始设计吧! 我们将使用EventManager.h文件来包含在类定义之上的所有小部件。我们需要定义的第一件事是我们将要处理的所有事件类型。这可以在以后进行扩展，但是由于这将更适合我们现在的目的，所以我们现在还不需要担心这个问题。让我们编写枚举表：

```c++
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
```

​		其中大部分都是真实事件;但是，请注意终止枚举之前的最后一行。我们正在设置自己的事件，称为Keyboard，其值为sf:: event::Count + 1。因为所有的枚举本质上都是指向整数值的关键字，最后一行防止任何类型的标识符冲突，并确保添加到此点之后的任何东西都高于绝对最大值sf::Event::EventType枚举值。只要最后一行之前添加的内容是有效的事件类型，就不应该有冲突。

> sf::Event 枚举值可以不同，这取决于您使用的SFML版本。

​		接下来，让我们为每个绑定存储这些事件组成为可能。我们知道，为了绑定到一个键，我们需要事件类型和我们感兴趣的键的代码。我们将处理的一些事件只需要存储一个类型，在这种情况下，我们可以简单地存储一个带有该类型的整数值0。了解了这一点，让我们定义一个新的结构来帮助我们存储这些信息:

```c++
struct EventInfo{
	EventInfo(){ m_code = 0; }
 	EventInfo(int l_event){ m_code = l_event; }
 	union{
 		int m_code;
 	};
};
```

​		为了给扩展留出空间，我们已经使用了一个union来存储事件代码。接下来，我们可以设置将要用来保存事件信息的数据类型:

```c++
	using Events = std::vector<std::pair<EventType, EventInfo>>;
```

​		因为我们将需要与使用这个类的代码共享事件信息，所以现在是设置一个数据类型来帮助我们完成这一任务的最佳时机：

```c++
struct EventDetails{
 	EventDetails(const std::string& l_bindName) : m_name(l_bindName){
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
```

​		现在是设计绑定结构的时候了，它将保存所有的事件信息。看起来很简单，我们来实现一下：

```c++
struct Binding{
 	Binding(const std::string& name)
 	: m_name(name), m_details(name), c(0){ }
 
    void BindEvent(EventType type, EventInfo info = EventInfo()){
 		m_events.emplace_back(type, info);
 	}
 
    Events m_events;
 	std::string m_name;
 	int c; // Count of events that are "happening".
 	EventDetails m_details;
};
```

​		构造函数接受我们想要将事件绑定到的动作的名称，并使用初始化器列表来设置类数据成员。我们还有一个BindEvent()方法，它只接受事件类型和事件信息结构，以便将其添加到事件向量中。我们之前没有提到的另一个数据成员是名称为c的整数。正如注释所暗示的那样，这将跟踪实际发生的事件的数量，这将在稍后用于确定绑定中的所有键和事件是否“on”。最后，这是共享的事件细节数据成员所在的结构。

​		这些绑定也必须以某种方式存储，所以让我们为负责它的容器定义数据类型：

```c++
using Bindings = std::unordered_map<std::string, Binding*>;
```

​		将std::unordered_map用于绑定可以保证每个操作只有一个绑定，因为它是一个关联容器，而操作名称字符串是该容器的键。

​		到目前为止，我们做得很好，但是，没有办法将这些操作与将要被调用的有效方法联系起来，这个系统相当没用。我们来讨论一下如何实现它。在计算机科学的世界中，您可能不时听到“"callback”这个术语。用最简单的术语来说，回调是作为参数传递给另一段代码的一些代码块，另一段代码将在方便的时候执行它。在我们的事件管理器中，最方便的时间是绑定到特定操作的所有事件发生时，而回调是表示正在执行的操作的方法。假设，我们希望字符在按下空格键时跳跃。我们将创建一个名为“Jump”的绑定，这是我们的动作名，并添加一个类型为KeyDown和代码sf::Keyboard::Space的单个事件。为了便于论证，我们假设这个字符有一个名为Jump()的方法。这是我们的回调。我们希望将该方法绑定到名称“Jump”，并让事件管理器在按下空格键时调用角色的Jump()方法。简而言之，这就是我们在新系统中处理输入的方法。

​		到目前为止，您的c++背景可能会驱使您使用术语“函数指针”。虽然这未必是一个坏的选择，但如果您是新手，可能会有点混乱。这种方法的主要问题是将类的方法添加为回调。指向类成员的指针与常规函数并不完全相同，除非它是一个静态方法。下面是成员函数指针的基本定义：

```c++
void(SomeClass::*_callback)(  );
```

​		这已经显示了一些主要的限制。首先，我们只能有指向“SomeClass”类方法的指针。其次，如果没有一个具有我们所指向的方法的类的实例，它是非常无用的。您可能会有这样的想法:将实例和函数指针一起存储在某个回调结构中。让我们看一看：

```c++
struct Callback{
 	std::string m_name;
 	SomeClass* CallbackInstance; // Pointer to instance.
 	void(SomeClass::*_callback)();
    
    void Call(){
 		CallbackInstance->*_callback();
 	}
};
```

​		好一点了。至少我们现在可以调用这个方法了，尽管我们仍然只局限于一个类。我们可以将其他类方法调用封装在“SomeClass”类的方法中，但这很乏味，更重要的是，这是一个糟糕的实践。也许现在您正在想一些模板魔法可能会解决这个问题。也许现在您正在想一些模板魔法可能会解决这个问题。考虑一下这可能需要的最小的努力：

```c++
template<class T>
	struct Callback{
	...
	T* CallbackInstance; // Pointer to instance.
 	void(T::*_callback)();
 	...
};
```

​		这本身并不能解决任何问题，反而会带来更多的问题。首先，您现在必须在事件管理器类中定义该模板，这是有问题的，因为我们需要为所有这些回调提供一个容器，这意味着必须对整个事件管理器类进行模板化，这将其锁定为一个类类型。首先，您现在必须在事件管理器类中定义该模板，这是有问题的，因为我们需要为所有这些回调提供一个容器，这意味着必须对整个事件管理器类进行模板化，这将其锁定为一个类类型。我们又回到了原点。使用typedef是一个聪明的想法，除了它不支持大多数Visual Studio编译器的这种形式:

```c++
template <class T>
using Function = void (T::*)();
```

​		对于非c++ 11编译器，有一些hack式的变通方法，比如在定义模板后在struct中包装typedef。然而，这也不能解决我们的问题。在使用“模板化”成员函数指针类型定义时，曾经出现过Visual Studio 2010编译器崩溃的例子。这相当混乱，此时您可能正在考虑简单地返回常规函数指针，并将每个成员函数调用包装在一个不同的函数中。不用担心，c++ 11引入了一种比这更好的方法。

## 4.6 Standard function wrapper

​		c++实用程序库为我们提供了优雅地解决这个难题所需要的:std::function和std::bind。 std::function类型是一个通用的多态函数包装器。在它支持的许多其他功能中，它可以存储成员函数指针并调用它们。让我们来看一个使用它的最小示例：

```c++
#include <functional> // Defines std::function & std::bind.
...
std::function<void(void)> foo = std::bind(&Bar::method1, this);
```

​		在本例中，我们实例化一个名为“foo”的函数包装器，它保存一个签名为void(void)的函数。在等号的右边，我们使用std::bind将类“Bar”的成员函数“method1”绑定到foo对象。第二个参数(因为这是一个成员函数指针)是将其方法注册为回调的类的实例。它必须是Bar类的一个实例，假设这行代码写在它的实现中传入"this"。现在我们的foo对象绑定到Bar类的方法method1。因为std::function重载了圆括号操作符，所以调用它就像这样简单：

```c++
foo(); // Equivalent to barInstance->method1();
```

​		现在我们终于可以定义回调容器的类型了:

```C++
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
```

​		再一次，使用std::unordered_map确保每个操作只有一个回调。如果需要，可以稍后更改。

## 4.7 Building the event manager

​		此时，我们已经具备了实际编写事件管理器类的头文件所需的一切。考虑到我们之前做出的所有设计决定，它应该看起来像下面这样：

```c++
class EventManager{
  public:
 	EventManager();
 	~EventManager();
 	bool AddBinding(Binding *l_binding);
 	bool RemoveBinding(std::string l_name);
    void SetFocus(const bool& l_focus);
    
    // Needs to be defined in the header!
 	template<class T>
 	bool AddCallback(const std::string& l_name, void(T::*l_func)(EventDetails*), T* l_instance){
 		auto temp = std::bind(l_func,l_instance, std::placeholders::_1);
 		return m_callbacks.emplace(l_name, temp).second;
 	}
 	void RemoveCallback(const std::string& l_name){
 		m_callbacks.erase(l_name);
 	}
 	void HandleEvent(sf::Event& l_event);
 	void Update();
 	sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr){
 		return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
 	}
    
  private:
 	void LoadBindings();
 	Bindings m_bindings;
 	Callbacks m_callbacks;
 	bool m_hasFocus;
};
```

​		从类定义中可以看出，我们仍然需要为AddCallback()方法使用模板化的成员函数指针参数。然而，使用std::function将其隔离为一个方法，这意味着我们不必对整个类进行模板化，这是一种改进。在将指向方法的指针和类的实例，以及将来将被实参替换的单个占位符绑定到临时函数之后，我们将它插入回调容器中。由于编译器处理模板化类的方式，我们需要在头文件中实现我们的AddCallback()方法，而不是.cpp文件。为了保持一致性，并且因为它是一个非常简单的方法，我们也在头文件中定义了RemoveCallback()。

​		关于头文件的另一件值得指出的事情是用于获取鼠标位置的方法的实现:GetMousePos()。它接受一个指向类型为sf::RenderWindow的指针，以防我们希望返回的坐标是相对于特定窗口的。同一个窗口也可以有或失去焦点，所以一个标志m_hasFocus是保持跟踪。

## 4.8 Implementing the event manager

​		让我们从实际实现所有事件管理器类方法开始，一如既往地从构造函数和析构函数开始：

```c++
EventManager::EventManager(): m_hasFocus(true){ 
    LoadBindings(); 
}
EventManager::~EventManager(){
 	for (auto &itr : m_bindings){
 		delete itr.second;
 		itr.second = nullptr;
 	}
}
```

​		在这种情况下，构造函数的工作非常简单。它所要做的就是调用一个私有方法LoadBindings()，该方法用于从文件中加载绑定的信息。我们很快就会讲到：

​		对于这种类型的类，析构函数的工作也是相当普通的。如果您还记得，我们将绑定存储在堆上，因此必须取消对这个动态内存的分配。

​		让我们看一下AddBinding方法的实现：

```c++
bool EventManager::AddBinding(Binding *binding){
 	if (m_bindings.find(binding->m_name) != m_bindings.end())
 		return false;
 	return m_bindings.emplace(binding->m_name, binding).second;
}
```

​		如您所见，它接受一个指向绑定的指针。然后检查绑定容器是否已经有同名的绑定。如果是，该方法将返回false，这对于错误检查很有用。如果没有名称冲突，则将新绑定插入到容器中。

​		我们有添加绑定的方法，但是如何删除它们呢?这就是RemoveBinding方法的作用所在:

```c++
bool EventManager::RemoveBinding(std::string name){
 	auto itr = m_bindings.find(name);
 	if (itr == m_bindings.end()){ return false; }
 	delete itr->second;
 	m_bindings.erase(itr);
 	return true;
}
```

​		它接受一个字符串参数，并在容器中搜索匹配项，将其存储到迭代器中。如果找到了匹配项，它首先通过删除键-值对中的第二个元素来释放内存，这是为绑定对象分配的动态内存，然后在返回true之前不久从容器中删除该条目。容易。

​		正如设计这个类的规范中所提到的，我们需要一种方法来处理在每次迭代中轮询的SFML事件，以便查看它们并查看其中是否有我们感兴趣的内容。这就是HandleEvent的作用所在:

```c++
void EventManager::HandleEvent(sf::Event& l_event){
 	// Handling SFML events.
 	for (auto &b_itr : m_bindings){
 		Binding* bind = b_itr.second;
 		for (auto &e_itr : bind->m_events){
 			EventType sfmlEvent = (EventType)l_event.type;
 			if (e_itr.first != sfmlEvent){ continue; }
 			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
 				if (e_itr.second.m_code == l_event.key.code){
 					// Matching event/keystroke.
 					// Increase count.
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 					break;
 				}
 			} else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
                if (e_itr.second.m_code == l_event.mouseButton.button){
 					// Matching event/keystroke.
 					// Increase count.
 					bind->m_details.m_mouse.x = l_event.mouseButton.x;
 					bind->m_details.m_mouse.y = l_event.mouseButton.y;
 					if (bind->m_details.m_keyCode != -1){
 						bind->m_details.m_keyCode = e_itr.second.m_code;
 					}
 					++(bind->c);
 					break;
 				}
 			} else {
 				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel){
 					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
 				} else if (sfmlEvent == EventType::WindowResized){
 					bind->m_details.m_size.x = l_event.size.width;
 					bind->m_details.m_size.y = l_event.size.height;
 				} else if (sfmlEvent == EventType::TextEntered){
 					bind->m_details.m_textEntered = l_event.text.unicode;
 				}
 				++(bind->c);
 			}
 		}
 	}
}
```

​		它适当地接收了一个sf::Event类型的参数。然后，该方法必须遍历所有绑定并遍历绑定内的每个事件，以检查l_event参数的类型是否与当前正在处理的绑定事件的类型匹配。如果是，则检查它是键盘事件还是鼠标事件，因为这涉及到进一步检查键盘键或鼠标按钮是否与所需的绑定匹配。如果是其中之一，最后一步是检查键盘键代码或鼠标按钮代码，它们分别存储在l_event中。如果是其中之一，最后一步是检查分别存储在l_event.key和l_eventmouse.Button结构中的键盘键代码或鼠标按钮代码是否与绑定事件的代码匹配。如果是这样的话，或者，如果是不需要进一步处理的不同类型的事件，如下面几行所示，则增加绑定实例的成员c，以在相关事件信息存储在绑定的事件详细信息结构中后不久表示匹配。

​		最后，对于输入处理，我们需要一个update方法，它可以处理实时输入检查以及绑定状态的验证和重置。让我们把它写：

```c++
void EventManager::Update(){
 	if (!m_hasFocus){ return; }
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
```

​		我们再一次遍历所有绑定及其事件。然而，在这种情况下，我们只对键盘、鼠标和操纵杆感兴趣，因为这些是我们唯一可以检查实时输入的设备。与以前很像，我们检查正在处理的事件类型，并使用适当的类检查输入。像往常一样，递增绑定类的c成员是我们注册匹配的方法。最后一步是检查事件容器中的事件数是否与“开启”的事件数匹配。如果是这样，我们将回调函数定位到m_callbacks容器中，并使用圆括号操作符调用第二个数据成员，因为它是一个std::function方法包装器，从而正式实现回调函数。我们将包含所有事件信息的EventDetails结构的地址传递给它。之后，为下一次迭代将活动事件计数器c重置为0是很重要的，因为之前检查的任何事件的状态都可能已经更改，它们都需要重新计算。

​		最后，如果您从上到下查看代码，您可能会注意到控制器输入的情况没有做任何事情。事实上，我们甚至不处理任何与控制器相关的事件。这是可以在以后扩展的内容，并且对我们的任何项目都不重要。如果你想要添加对操纵杆的支持并能够使用它，那就把它当成本章之后的功课吧。

​		既然我们已经具备了所有这些功能，为什么不实际地从文件中读取一些绑定信息呢?让我们看一下名为keys.cfg的配置示例, 我们将加载:

```c++
Window_close 0:0
Fullscreen_toggle 5:89
Move 9:0 24:38
```

​		可以用任何您想要的方式格式化它，但是，为了简单起见，它的布局在这里仍然是非常基本的。每一行都是一个新的绑定。它以绑定名开始，随后是事件类型枚举的数字表示，以及用冒号分隔的事件代码。每个不同的事件键:值对由空格、绑定名和事件开始部分分隔。让我们把这个读进去：

```c++
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
```

​		我们首先尝试打开keys.cfg文件。如果失败，该方法将输出一条控制台消息通知我们。接下来，我们进入一个while循环，以便读取文件中的每一行。我们定义了一个std::stringstream对象，它允许我们使用>>操作符将字符串一块一块地“stream”起来。它使用默认的空格分隔符，这就是为什么我们在配置文件中做出这样的决定。在获得绑定的名称后，我们创建一个新的绑定实例，并在构造函数中传递该名称。然后，通过继续进入一个while循环并使用!keystream.eof()作为参数，我们确保它一直循环到std::stringstream对象到达它所读取的行末尾。这个循环对每个key:value对运行一次，这再次归功于std::stringstream及其重载的>>操作符，默认情况下使用空格作为分隔符。

​		在流化事件的类型和代码之后，我们必须确保将它从一个字符串转换为两个整数值，然后将它们存储在各自的本地变量中。它接受前面读取的字符串的部分，以便通过分隔符分隔key:value对，在本例中，该方法的最顶部定义为“:”。如果在字符串中没有找到该字符，则删除绑定实例并跳过该行，因为该行很可能没有正确格式化。如果不是这样，则成功地绑定事件，并将代码转移到下一对。

​		一旦读入了所有的值并且到达了行尾，我们就尝试将绑定添加到事件管理器。这是在if语句中完成的，以便捕获我们前面谈到的与绑定名称冲突有关的错误。如果有冲突，绑定实例将被删除。

​		您可能已经知道，在使用该文件之后关闭该文件也很重要，所以这是在此方法结束之前我们要做的最后一件事。完成这些之后，我们的事件管理器终于完成了，是时候实际使用它了。

## 4.9 Integrating the Event Manager class

​		因为事件管理器需要检查所有被处理的事件，所以将其保存在窗口类中是有意义的，我们实际上在窗口类中进行事件轮询。毕竟，我们正在处理的事件都来自打开的窗口，因此只有在这里保留事件管理器的实例才有意义。让我们通过向窗口类添加一个数据成员来对其进行轻微的调整。

```c++
class Window{
  public:
 	...
 	bool IsFocused();
	EventManager* GetEventManager();
 	void ToggleFullscreen(EventDetails* l_details);
 	void Close(EventDetails* l_details = nullptr);
 	...
  private:
 	...
 	EventManager m_eventManager;
 	bool m_isFocused;
};
```

​		除了添加一个额外的方法来获取事件管理器之外，全屏切换方法已经修改为接受EventDetails结构作为参数。窗口类中还添加了一个Close方法，以及一个跟踪窗口是否处于焦点的标志。关闭窗口本身的方法很简单，只需要将一个标记设置为true:

```c++
void Window::Close(EventDetails* l_details){ m_isDone = true; }
```

​		现在是调整Window::Update方法并将所有正在轮询的事件传递到事件管理器的时候了:

```c++
void Window::Update(){
    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::LostFocus){
            m_isFocused = false;
            m_eventManager.SetFocus(false);
        } else if(event.type == sf::Event::GainedFocus){
            m_isFocused = true;
            m_eventManager.SetFocus(true);
        }
        m_eventManager.HandleEvent(event);
    }
    m_eventManager.Update();
}
```

​		这确保了在窗口中被分派的每个单个事件都将得到正确的处理。如果窗口的焦点发生变化，它还会通知事件管理器。

​		是时候实际使用事件管理器了! 让我们在Window::Setup中，在创建事件管理器的新实例之后，注册两个回调到一些成员函数:

```c++
void Window::Setup(...){
 	...
 	m_isFocused = true; // Default value for focused flag.
 	m_eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullscreen,this);
 	m_eventManager.AddCallback("Window_close", &Window::Close,this);
 	...
}
```

​		让我们回头看看keys.cfg文件。我们定义了Fullscreen_toggle操作，并设置了一个5:89的键值对，它实际上被分解为KeyDown事件类型(数字5)和键盘上F5键的代码(数字89)。这两个值都是我们使用的枚举的整数表示。

​		另一个被设置的回调函数是操作Window_close，它在配置文件中被绑定到0:0。事件类型0对应于枚举表中的Closed，代码是无关的，所以我们也将其设置为0。

​		这两个操作都绑定到Window类的方法。注意AddCallback方法中的最后一个参数，它是一个this指针，指向窗口的当前实例。在成功编译和启动之后，您应该会发现按下键盘上的F5键会切换窗口的全屏模式，单击close按钮实际上会关闭窗口。奏效了！现在我们来做一些更有趣的事情。	

## 4.10 Moving a sprite revisited

​		现在我们有了一个很棒的事件管理器，让我们在按住shift键和鼠标左键时将精灵移动到鼠标位置上，从而全面测试它。添加两个新的数据成员到你的Game类:m_texture和m_sprite。按照前几章所讨论的方式进行设置。出于我们的目的，我们将重复使用前几章中的蘑菇图形。现在在游戏类中添加并实现一个名为MoveSprite的新方法：

```c++
void Game::MoveSprite(EventDetails* l_details){
 	sf::Vector2i mousepos = m_window->GetEventManager()->GetMousePos(m_window->GetRenderWindow());
 	m_sprite.setPosition(mousepos.x, mousepos.y);
 	std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
}
```

​		我们在这里所做的是从事件管理器中获取相对于当前窗口的鼠标位置，并将其存储在一个名为mousepos的本地整数向量中。然后我们将精灵的位置设置为当前鼠标的位置，并在控制台窗口中打印出一个小句子。非常基本，但它可以很好地作为测试。让我们设置我们的callback：

```c++
Game::Game(){
 	...
 	// Texture and sprite setup
    ...
 	m_window->GetEventManager()->AddCallback("Move", &Game::MoveSprite,this);
}
```

​		我们将动作名称Move绑定到游戏类的MoveSprite方法，并传递一个指向当前实例的指针，就像之前一样。在运行之前，让我们先看看keys.cfg文件中定义move操作的方式:

```c++
Move 9:0 24:38
```

​		第一个事件类型对应于MButtonDown，它是鼠标左键被按下的事件。第二个事件类型对应于键盘事件，它通过sf::Keyboard类检查实时输入。数字38是左shift键代码，对应sf::Keyboard::LShift。

​		在编译和执行我们的应用程序时，我们应该在屏幕上呈现一个精灵。如果我们按住左shift并左键点击屏幕上的任何地方，它就会神奇地移动到那个位置!

## 4.11 Principles of use

​		即使在这种设计中，知道何时使用哪种类型的事件也很重要。例如，我们假设，你只希望一个回调函数被调用一次，用于涉及左移和R键的绑定。您不能将这两种事件类型都定义为Keyboard，因为只要这些键处于down状态，它就会一直调用callback方法。您也不希望将它们都定义为KeyDown事件，因为这意味着必须同时注册这两个事件，而在按住多个键时，由于屏幕刷新率的原因，这很可能不会发生。正确的使用方法是混合Keyboard和KeyDown事件，以便最后一个按下的键是KeyDown类型，其余的键是Keyboard类型。在我们的示例中，这意味着我们将通过sf::Keyboard类检查左shift键，而R键将默认为正在调度的事件。这听起来可能有点奇怪，但是，考虑一下著名的组合键Ctrl + Alt + Del在你的计算机上的例子。它是这样工作的，但如果你按相反的顺序拿钥匙，它什么也做不了。如果我们实现这个功能，我们很可能会确保Ctrl和Alt键总是通过sf::Keyboard类进行检查，而Del键是通过事件轮询注册的。

​		对于这个类的使用，需要注意的最后一点是，有些事件还不支持，比如sf::Event::TextEntered事件，因为为了充分利用它们需要额外的信息，这些信息是从sf::Event类获得的。适当扩展事件管理器以支持这些特性将在后面的章节中讨论，一旦我们处理需要上述事件的问题。

## 4.12 Common mistakes

​		新来的人在使用SFML输入时最常见的错误之一是使用某些方法检查用户输入是否有错误的任务，例如使用窗口事件进行实时字符移动或捕获文本输入。了解你所使用的任何东西的局限性是培养任何一种良好表现的关键。为了获得最佳结果，请确保坚持我们讨论过的所有不同机制的预期用途。

​		们经常犯的另一个错误是在.cpp文件中而不是头文件中定义模板。如果你正在连接错误,用于修饰或说明一种方法就是这样利用模板,如EventManager: AddCallback()方法,确保移动的实现方法和模板的定义你的类的头,否则编译器无法实例化模板和方法在连接过程中变得难以接近。

​		最后，许多SFML的新用户犯的一个相当简单但非常流行的错误是不知道如何正确地获取相对于窗口的鼠标坐标。它的范围从简单地使用错误的坐标并经历奇怪的行为，到获取相对于桌面的坐标以及窗口的位置并相减以获得本地鼠标位置。虽然后者可以工作，但有点过分，特别是自从SFML已经为您提供了一种无需重复工作的方法。只需将窗口的引用传递给sf::Mouse::getPosition()方法。这就是你所需要的。

# 5 Can I Pause This? – Application States

## 5.1 What is a state?

​		在我们开始任何一种实现之前，有必要了解我们要处理的是什么。如果你之前阅读过任何类型的游戏开发材料，你可能会遇到state这个术语。根据上下文，它可以有不同的含义。在这种情况下，状态是游戏的许多不同层面中的任何一个，如主菜单、菜单显示前的游戏介绍或实际的游戏玩法。当然，每一层都有自己更新自身和在屏幕上呈现内容的方式。当使用这个系统时，游戏开发者的工作是将给定的问题分解成独立的、可管理的状态和它们之间的转换。当使用这个系统时，游戏开发者的工作是将给定的问题分解成独立的、可管理的状态和它们之间的转换。

## 5.2 The most simplistic approach

​		让我们首先说明新手为了解决这个问题所采用的最常见的方法。它首先列举游戏可能存在的所有可能状态：

```c++
enum class StateType{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};
```

​		良好的开端。现在让我们简单地使用switch语句来让它工作:

```c++
void Game::Update(){
	switch(m_state){
 	  case(StateType::Intro):
 		UpdateIntro();
 		break;
 	  case(StateType::Game):
	    UpdateGame();
 		break;
 	  case(StateType::MainMenu):
 		UpdateMenu();
		break;
 	  ...
 	}
}
```

​		同样的道理也适用于在屏幕上绘图:

```c++
void Game::Render(){
	switch(m_state){
 	  case(StateType::Intro):
 		DrawIntro();
 		break;
 	  case(StateType::Game):
 		DrawGame();
 		break;
 	  case(StateType::MainMenu):
 		DrawMenu();
 		break;
 	  ...
 	}
}
```

​		虽然这种方法适用于小型游戏，但可扩展性却是完全不可能的。首先，当添加更多的状态时，switch语句将继续增长。假设我们只将更新和呈现特定状态的功能本地化到一个方法上，这些方法的数量也将继续增加，每个状态至少有两个方法，其中一个用于更新，另一个用于呈现。请记住，这是支持额外状态所需的最小扩展量。如果我们还单独处理每个状态的事件或执行某种额外的逻辑(如后期更新)，则需要四条switch语句、每个状态的一个额外的switch分支以及四个必须实现并添加到分支的额外方法。

​		接下来，考虑状态转换。如果出于某种原因，您希望在短时间内同时呈现两个状态，那么整个方法就会崩溃。它仍然可能以某种方式串起来的功能，通过捆绑一串标志或创建组合状态如下:

```c++
enum StateType{
	Intro = 1, Intro_MainMenu, MainMenu, Game, MainMenu_Game
 	Paused, GameOver, MainMenu_GameOver, Credits, MainMenu_Credits
 	...
 	// Crying in the corner.
};
```

​		这变得越来越混乱，我们甚至还没有扩展我们已经很大的switch语句，更不用说实现我们想要的所有状态了!

​		如果您现在还没有考虑使用不同的策略，那么考虑最后一点:资源。如果你同时保存了游戏可能加载的所有可能状态的所有数据，从效率的角度来看，你可能会遇到相当大的问题。您可以动态地分配代表某些状态的类，并检查它们何时不再使用，以某种方式重新分配它们，然而，这在您已经几乎不可读的代码基中增加了额外的混乱，既然您已经在考虑使用类，为什么不做得更好呢?

## 5.3 Introducing the state pattern

​		前面提到的所有问题都可以通过仔细的白板和考虑来避免。前面提到的所有问题都可以通过仔细的白板和考虑来避免。所有这些类都将共享用于更新和呈现的相同方法，这使得继承成为热门话题。让我们看看我们的BaseState 头文件:

```c++
class StateManager;

class BaseState{
	friend class StateManager;
  public:
 	BaseState(StateManager* stateManager):m_stateMgr(stateManager),m_transparent(false),m_transcendent(false){}
 	virtual ~BaseState(){}
 	virtual void OnCreate() = 0;
 	virtual void OnDestroy() = 0;
 	virtual void Activate() = 0;
 	virtual void Deactivate() = 0;
 	virtual void Update(const sf::Time& l_time) = 0;
 	virtual void Draw() = 0;
 	void SetTransparent(const bool& l_transparent){
 		m_transparent = l_transparent;
 	}
 	bool IsTransparent()const{ return m_transparent; }
 	void SetTranscendent(const bool& l_transcendence){
 		m_transcendent = l_transcendence;
 	}
    bool IsTranscendent()const{ return m_transcendent; }
 	StateManager* GetStateManager(){ return m_stateMgr; }
  protected:
 	StateManager* m_stateMgr;
 	bool m_transparent;
 	bool m_transcendent;
};
```

​		首先，您会注意到我们使用了StateManager类的前向声明。基类实际上不需要知道任何关于状态管理器实现方式的信息，只需要保持一个指向它的指针。这样做也是为了避免递归定义，因为StateManager类头文件需要包含BaseState类头文件。

​		由于我们希望在所有状态下强制使用相同的方法，所以我们将它们设置为纯虚方法，这意味着从BaseState继承的类必须实现它们中的每一个，以便项目能够编译。任何派生类都必须实现方法OnCreate和OnDestroy，当状态被创建并压入堆栈时调用，然后从堆栈中删除，Activate和Deactivate，当状态移动到堆栈顶部时，以及从顶部位置删除时，都会调用这两个函数，最后是Update和Draw，它们用于更新状态和绘制其内容。

​		关于这个类要注意的最后一点是，它有一对标志:m_transparent和m_transcendent。这些标志指示此状态是否也需要呈现或更新之前的状态。这消除了对状态之间不同转换的无数枚举的需要，并且可以在不进行任何额外扩展的情况下自动完成。

## 5.4 Defining common types

​		在前面的例子中，我们肯定要保留的一个东西是状态类型的枚举表:

```c++
enum class StateType{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};
```

​		枚举状态类型很方便，并且有助于自动创建状态，稍后您将看到这一点。

​		我们需要保留的另一种常见类型是我们将与状态一起使用的设备上下文。不要被名称搞糊涂了，它只是表示有一个指针，指向我们最常用的类或“设备”。因为有不止一个，定义一个简单的结构来保存指向主窗口类和事件管理器的指针是非常有用的:

```c++
struct SharedContext{
	SharedContext():m_wind(nullptr),m_eventManager(nullptr){}
 	Window* m_wind;
 	EventManager* m_eventManager;
};
```

​		这可以在以后需要时进行扩展，以便保存有关玩家和其他处理资源分配、声音和网络的助理类的信息。

## 5.5 The state manager class

​		现在我们已经建立了帮助结构，让我们实际定义用于在状态管理器类中保存信息的类型。一如既往，我们将使用类型定义，其优点在于，在修改类型定义时，它们减少了需要更改的代码数量。让我们先看看状态容器类型:

```c++
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
```

​		同样，我们用的是向量。元素类型是一对状态类型和一个指向BaseState类型对象的指针。您可能想知道为什么map不是更好的选择，答案取决于您的实现理念，然而，一个主要因素是map在容器中不保持堆栈式的顺序，如果我们希望状态管理器正确工作，这一点很重要。

​		状态管理器类中的一个设计决策也需要一个状态类型的容器，所以让我们定义它:

```c++
using TypeContainer = std::vector<StateType>;
```

​		如您所见，它只是一个StateType枚举类型的向量。

​		需要定义的最后一个类型是用于自定义函数的容器，它将作为一种方法自动生成源自的不同类型对象BaseState类:

```c++
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;
```

​		我们在这里使用无序映射，以便将特定的状态类型映射到将生成该类型的特定函数。如果这听起来令人困惑，请耐心等待。当我们真正使用它的时候，它会被覆盖得更彻底。

## 5.6 Defining the state manager class

​		现在，我们需要为状态管理器类创建一个头文件的所有单独的部分都已经存在了，所以让我们来编写它:

```c++
class StateManager{
  public:
	StateManager(SharedContext* l_shared);
 	~StateManager();
    
 	void Update(const sf::Time& l_time);
 	void Draw();
    
 	void ProcessRequests();
    
 	SharedContext* GetContext();
 	bool HasState(const StateType& l_type);
    
 	void SwitchTo(const StateType& l_type);
 	void Remove(const StateType& l_type);
  private:
 	// Methods.
 	void CreateState(const StateType& l_type);
 	void RemoveState(const StateType& l_type);
    
 	template<class T>
 	void RegisterState(const StateType& l_type){...}
    
 	// Members.
 	SharedContext* m_shared;
 	StateContainer m_states;
 	TypeContainer m_toRemove;
 	StateFactory m_stateFactory;
};
```

​		构造函数接受一个指向我们前面谈到的SharedContext类型的指针，该类型将在我们的主Game类中创建。不出所料，状态管理器还使用了Update和Draw方法，因为它将由Game类操作，而且保持界面的熟悉性很好。为了方便起见，它提供了获取上下文以及确定当前是否在堆栈上有某种状态的helper方法。

​		public方法的最后一种是SwitchTo，它接受状态类型，并将当前状态更改为对应于该类型的状态;还有Remove，用于根据状态类型从状态堆栈中移除状态。

​		如果您从上到下查看类定义，您可能已经注意到我们有一个名为m_toRemove的TypeContainer成员。为了确保平滑和无错误的转换，我们不能在任何时候简单地从状态容器中删除任何我们想要的状态。这里的一个简单解决方案是跟踪我们想要删除的状态类型，并且只在不再使用它们时才删除它们，这就是ProcessRequests方法所做的事情。它在游戏循环中最后被调用，以确保m_toRemove容器中的状态不再被使用。

​		在下一节中，让我们继续使用更高级的私有方法和状态管理器类的实现。

## 5.7 Implementing the state manager

​			为了维护在堆上创建状态的自动化方法，我们必须有一些定义如何创建它们的方法。m_stateFactory成员是一个将状态类型链接到std::function类型的映射，我们可以通过使用lambda表达式将其设置为保存函数体:

```c++
template<class T>
void RegisterState(const StateType& l_type){
 	m_stateFactory[l_type] = [this]() -> BaseState*{
 		return new T(this);
 	};
}
```

​		上面的代码将m_stateFactory映射中的类型l_type映射到一个函数，该函数只返回一个指向新分配的内存的指针。我们在这里使用模板是为了减少代码量。因为每个状态都需要一个指向其构造函数中的StateManager类的指针，所以我们将this指针传入。我们现在可以像这样注册不同的状态:

```c++
StateManager::StateManager(SharedContext* l_shared): m_shared(l_shared){
    RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
 	RegisterState<State_Game>(StateType::Game);
 	RegisterState<State_Paused>(StateType::Paused);
}
```

​		现在是时候开始实现这个类的其余部分了。让我们看看析构函数:

```c++
StateManager::~StateManager(){
     for (auto &itr : m_states){
 		itr.second->OnDestroy();
 		delete itr.second;
 	}
}
```

​		因为我们将任何状态的所有动态内存分配都本地化到这个类，所以必须适当地释放内存。遍历所有状态并删除组成元素的pair的第二个值就是这样做的。

​		接下来，让我们看看如何实现draw方法:

```c++
void StateManager::Draw(){
	if (m_states.empty()){ return; }
 	if (m_states.back().second->IsTransparent() && m_states.size() > 1){
 		auto itr = m_states.end();
 		while (itr != m_states.begin()){
 			if (itr != m_states.end()){
 				if (!itr->second->IsTransparent()){
 					break;
 				}
 			}
 		--itr;
 		}
 		for (; itr != m_states.end(); ++itr){
 			itr->second->Draw();
 		}
 	} else {
 		m_states.back().second->Draw();
 	}
}
```

