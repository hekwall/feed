/*
 * FILNAMN:       firstboss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "firstboss.h"
#include "messagequeue.h"
#include "util.h"
#include <iostream>
#include "audio.h"

namespace feed
{
    FirstBoss::FirstBoss(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor,
               const glm::vec2& boundary_start,
               const glm::vec2& boundary_end)
        : Boss(position,
               size,
               velocity,
               image,
               hitpoints,
               armor,
               boundary_start,
               boundary_end)
    {
        addWeapon(Weapon::BOSS_PISTOL);
        addWeapon(Weapon::BOSS_SHOTGUN);
        addWeapon(Weapon::BOSS_SMG);
    }

    void FirstBoss::update(float delta_time)
    {
        // Död
        if (hitpoints_ <= 0)
            isDead();

        // Patrullering
        if (position_.x + size_.x >= boundary_end_.x)
        {
            velocity_.x = -abs(velocity_.x);
        }       
        else if (position_.x <= boundary_start_.x)
        {
            velocity_.x = abs(velocity_.x);
        }

        // Byter skjutriktning varannan sekund
        if (last_updated_aim_ + delta_time >= 2)
        {
            int r = rand() % 13;
            set_aim(glm::vec2(cos(r * aiming_constant_ * util::DEG_TO_RAD), -sin(r * aiming_constant_ * util::DEG_TO_RAD)));
            last_updated_aim_ = 0;
        }
        else
        {
            last_updated_aim_ += delta_time;
        }

        // Skjut
        fire();

        switch (phase_)
        {
            case PHASE_ONE:
                if (armor_ == 0)
                {
                    // Byt till fas 2
                    phase_ = PHASE_TWO;
                    ++inventory_index_;
                }

                // Fas 1

                break;

            case PHASE_TWO:
                if (!spawned_grunts_)
                {
                    MessageQueue::instance().pushMessage({MessageQueue::Message::SPAWN_ADDS_PHASE_TWO});
                    spawned_grunts_ = true;
                    Audio::instance().playSoundFx("minions-attack");
                }

                if (hitpoints_ <= max_health_ / 2)
                {   
                    // Byt till fas 3
                    phase_ = PHASE_THREE;
                    ++inventory_index_;
                }

                // Fas 2

                break;

            case PHASE_THREE:
                if (!spawned_heavys_)
                {
                    MessageQueue::instance().pushMessage({MessageQueue::Message::SPAWN_ADDS_PHASE_THREE});
                    spawned_heavys_ = true;
                    Audio::instance().playSoundFx("heed");

                }

                // Fas 3

                break;
        }

        Boss::update(delta_time);
    }

    void FirstBoss::isDead()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::FIRST_BOSS_DEAD});
    }
}
