/*
 * FILNAMN:       mainmenu.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Spelets huvudmeny.
 *
 */

#ifndef FEED_MAIN_MENU_H
#define FEED_MAIN_MENU_H

#include "state.h"
#include "menu.h"

#include <glm/glm.hpp>

namespace feed
{
    class MainMenu : public State
    {
    public:
        MainMenu(SDL_Surface* background, const glm::vec2& position);

        virtual void draw(SDL_Surface* screen) override final;
        virtual void update(float) override final {};
        virtual void handleSDLEvent(const SDL_Event& event) override final;
        virtual void handleMessage(const MessageQueue::Message& msg) override final;

    private:
        Menu main_;
    };
}

#endif
