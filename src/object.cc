/*
 * FILNAMN:       object.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-15
 */

#include "object.h"
#include "util.h"
#include <iostream>

namespace feed
{
    Object::Object(const glm::vec2& position,
                   const glm::vec2& size,
                   const glm::vec2& velocity,
                   SDL_Surface* image)
        : position_(position)
        , size_(size)
        , velocity_(velocity)
        , bounding_box_(position_.x, position_.y, size_.x, position_.y)
    {
        image_ = new AnimatedImage(image);
    }

    glm::vec2 Object::get_position() const
    {
        return position_;
    }

    glm::vec2 Object::get_size() const
    {
        return size_;
    }

    glm::vec2 Object::get_velocity() const
    {
        return velocity_;
    }

    glm::vec4 Object::get_bounding_box() const
    {
        return bounding_box_;
    }

    glm::vec2 Object::get_center() const
    {
        return glm::vec2(position_.x + size_.x / 2, position_.y + size_.y / 2);
    }

    // Aktiverar animering
    void Object::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->setAnimated(nof_animations, nof_frames);
    }

    void Object::setTopImage(SDL_Surface* sheet, unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->addTopImage(sheet, nof_animations, nof_frames);
    }

    void Object::set_position(const glm::vec2& position)
    {
        position_ = position;
    }

    void Object::set_size(const glm::vec2& size)
    {
        size_ = size;
    }

    void Object::set_velocity(const glm::vec2& velocity)
    {
        velocity_ = velocity;
    }

    void Object::set_bounding_box(const glm::vec4& bounding_box)
    {
        bounding_box_ = bounding_box;
    }

    void Object::draw(SDL_Surface* screen, const glm::vec2& offset)
    {
        glm::vec2 off = offset - glm::vec2(util::PLAYER_OFFSET_X, util::PLAYER_OFFSET_Y);

        if (image_ != nullptr)
            image_->draw(screen, position_ - off);
    }

    void Object::update(float delta_time)
    {
        position_ += velocity_ * delta_time;

		if (image_ != nullptr)
            image_->update(delta_time);
    }
}
