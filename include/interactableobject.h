/*
 * FILNAMN:       interactableobject.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: 
 *
 */

#ifndef FEED_INTERACTABLE_OBJECT_H
#define FEED_INTERACTABLE_OBJECT_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "object.h"

namespace feed
{
    class InteractableObject : public Object
    {
    public:
        InteractableObject(const glm::vec2& position, const glm::vec2& size, SDL_Surface* image);

        void draw() override final;
        virtual void eventFunction() = 0;

    private:
        SDL_Surface* image_;
    };
}


 #endif