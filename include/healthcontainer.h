/*
 * FILNAMN:       healthcontainer.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: När spelaren interagerar med detta objekt kommer hans hítpoints att fyllas
 *              på med ett förutbestämt värde
 *
 */

#ifndef FEED_HEALTH_CONTAINER_H
#define FEED_HEALTH_CONTAINER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "interactableobject.h"

namespace feed
{
    class HealthContainer : public InteractableObject
    {
    public:
        HealthContainer(const glm::vec2& position,
                        const glm::vec2& size,
                        SDL_Surface* image,
                        int health_value);

        virtual void eventFunction() override final;
    private:
    	int health_value_;
    };
}

 #endif
