/*
 * FILNAMN:       state.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Abstrakt klass för ett state. States används för att separera delar av feed så som menyer och spelvärlden
 *
 */

#ifndef FEED_STATE_H
#define FEED_STATE_H

#include <SDL/SDL.h>
#include "messagequeue.h"

namespace feed
{
    class State
    {
    public:
        virtual ~State() {}

        virtual void draw(SDL_Surface* screen) = 0;
        virtual void update(float delta_time) = 0;
        virtual void handleSDLEvent(const SDL_Event& event) = 0;
        virtual void handleMessage(const MessageQueue::Message& msg) = 0;
    };
}

#endif
