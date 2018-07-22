//
// Created by darkblinx on 27/06/17.
//

#ifndef JAMENGINE_WINDOW_HPP
#define JAMENGINE_WINDOW_HPP

#include <SDL2/SDL.h>
#include <iosfwd>

namespace JamEngine {
    struct windowSettings;

    struct Window {

        explicit Window (windowSettings const &setting);

        SDL_Window *getWindow();

        operator  SDL_Window*()const { return m_window;}

        Window () = delete;

        Window(Window const &) = delete;

        Window operator=(Window const &) = delete;

        const windowSettings &getSettings() const;

        ~Window();

    private:
        SDL_Window *m_window;
        SDL_Joystick * m_joystick = nullptr;
        SDL_GameController * m_controller = nullptr;
        SDL_GLContext m_context;
        windowSettings const & settings;


        void initJoystick();
    };

}
#endif //GLENGINE_WINDOW_HPP
