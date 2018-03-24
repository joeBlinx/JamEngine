# JamEngine
2dEngine created for personal use in Game Jam. It is written in C++ 17 and use OpenGL API. (actually in development)

It works on Linux and Windows.

Tested on : Debian 8, Mint 18 and Windows 10

## Dependencies
* SDL2
* SDL2_image
* SDL2_mixer
* glm 
* CMake, at least 3.0

## Compiling
It use C++ 17 so you need a compatible compiler, g++-7 or MSVC 17 is fine.

## How it works 
All the code is wrap into the namespace JamEngine.
#### Scene
This class in a Singleton. You'll have very few interactions with this. You have only 4 methods that you will use :
* *add* : add an Entity
* *remove* : remove Entity without destroying it
* *delete* : remove and destroy Entity
* *clear* : remove all Entities

#### GameState 
Hold the GameLoop of your game. 
* *loop* : Call this to begin the game loop
* *gameOver* : call this anywhere in your code and it will end the loop


By default, the escape button and the cross on the Window trigger the end of the loop.
#### Window
Create your program window, it only take one thing in parameter `windowSettings` which handle all the parameter you need too create a simple window

#### Entity
Base class of all object in your game. You have to inherited from this class and you can override some function like :
* *update* : things to do every frame
* *collide* : define collision type and what to do when collision occur
* *display* : define how it will be display

To add your Entity to the Scene you need to use the `add` function of `Scene` :
```cpp
Entity a;
Scene::add(&a);
```
#### KeyEvent
To use the KeyEventHandler you need to prepare two things. First you need to write a config file to link a word to one or two keys. It look like this 
```
jump = space
move = w, z
```
Here `jump` is associated with the `space bar`, and `move` with the `w` and `z` keys. After that you need to tell to the KeyEventHandler which file to use with the init function.
```
KeyEventHandler::init("youFile");
```
Now the initialisation is correctly done. Two function are available to define if you want the action to be done when the key is pressed or released. 
```cpp
KeyEventHandler::addKeyEventPressed("move", []{//something});
KeyEventHandler::addKeyEventReleased("jump", []{//something else});
```
#### Event
You can add some event, anywhere, at anytime in your code. You define the duration of your event and what it does.
To do that, you only have to use the `addEvent` function of the Event Manager, it take two parameter. First it's the duration in second and the other is the function to execute each frame. The function must take one float parameter. It's the time since the first execution of this function. So you can add event like this
```cpp
EventManager::addEvent(5, [](float time){
    std::cout << "time since first execution " << time << " seconds" << std::endl;
};);
```
It will display this at every frame for 5 seconds.
Here I use a Lambda function, but you can use what you want.
