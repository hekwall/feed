/*
 * FILNAMN:       enemy.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 *                Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-29
 *
 */

#include "enemy.h"
#include "messagequeue.h"
#include "resources.h"

#include <iostream>


namespace feed
{
    Enemy::Enemy(const glm::vec2& position,
                 const glm::vec2& size,
                 const glm::vec2& velocity,
                 SDL_Surface* image,
                 int hitpoints,
                 int armor,
                 int max_health,
                 int max_armor,
                 int weapon_type,
                 const glm::vec2& boundary_start,
                 const glm::vec2& boundary_end)
        : Character(position, size, velocity, image, hitpoints, armor, max_health, max_armor)
        , boundary_start_(boundary_start)
        , boundary_end_(boundary_end)
    {
        weapon_ = Weapon::CreateWeapon(weapon_type, 100);

        if(boundary_end != glm::vec2(0,0))
        {
            velocity_ = glm::length(velocity)*glm::normalize(boundary_end - boundary_start);
            walking = true;
        }   
    }

    Enemy::~Enemy()
    {
        delete weapon_;
    }

    void Enemy::fire()
    {
        if (weapon_ != nullptr)
            if (weapon_->isReady())
            {
                MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, weapon_->get_type(), this});
                weapon_->fired();
            }
    }

    bool Enemy::get_seen_player() const
    {
        return seen_player_;
    }

    void Enemy::set_seen_player(bool value)
    {
        seen_player_ = value;
    }

    void Enemy::update(float delta_time)
    {
        set_seen_player(true);
        weapon_->update(delta_time);

        if (boundary_end_ != glm::vec2(0,0))
        {   
            glm::vec2 direction_ = glm::normalize(boundary_end_ - boundary_start_);

            if ((position_.x >= boundary_end_.x && position_.y <= boundary_end_.y && direction_.y <= 0) ||
                (position_.x >= boundary_end_.x && position_.y >= boundary_end_.y && direction_.y >= 0))
            {
                walkLeft();
            }
                    

            else if ((position_.x <= boundary_start_.x && position_.y >= boundary_start_.y && direction_.y <= 0) ||
                     (position_.x <= boundary_start_.x && position_.y <= boundary_start_.y && direction_.y >= 0))
            {
                 walkRight();
            }
                    
        }

        Character::update(delta_time);
    }

    void Enemy::walkLeft()
    {
        setAnimation(Character::WALKING_LEFT);
        velocity_ = - glm::length(velocity_)*glm::normalize(boundary_end_ - boundary_start_);
    }

    void Enemy::walkRight()
    {
        setAnimation(Character::WALKING_RIGHT);
        velocity_ = glm::length(velocity_)*glm::normalize(boundary_end_ - boundary_start_);
    }

    bool Enemy::isWalking() const
    {
        return walking;
    }


    ////////////////////////
    // Protected

    void Enemy::isDead()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::ENEMY_DEAD, 0, this});
    }

    ////////////////////////
    // "Factory"-funktioner

    Enemy* Enemy::CreateGrunt(const glm::vec2& position, const glm::vec2& boundary_start, const glm::vec2& boundary_end)
    {
        glm::vec2 size(30, 110);
        glm::vec2 velocity;

        if (boundary_end != glm::vec2(0,0))
            velocity = glm::vec2(50, 0);

        SDL_Surface* image = Resources::instance()["legs"];
        int hitpoints = 25;
        int armor = 0;
        int max_health = 25;
        int max_armor = 0;
        int weapon_type = Weapon::ENEMY_PISTOL;

        Enemy* enemy = new Enemy(position, size, velocity, image, hitpoints, armor, max_health, max_armor, weapon_type, boundary_start, boundary_end);
        enemy->setAnimated(4, 8);
        enemy->setTopImage(Resources::instance()["grunt-torso"], 2, 37);
        enemy->set_collision_offset(glm::vec2(50, 20));
        enemy->setAnimation(Character::WALKING_RIGHT);


        return enemy;
    }

    Enemy* Enemy::CreateHeavy(const glm::vec2 &position)
    {
        return nullptr;
    }
}
