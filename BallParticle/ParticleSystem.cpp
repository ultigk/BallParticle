#include <SFML/Graphics.hpp>
#include "window.h"
#include "ParticleSystem.h"


extern const sf::Vector2u WINDOW_SIZES;


Particle::Particle(const sf::Vector2f position, const sf::Vector2f velocity, 
    const sf::Vector2f acceleration, const float radius)
    : position_(position)
    , velocity_(velocity)
    , acceleration_(acceleration)
    , radius_(radius)
{
    CircleShape1.setRadius(radius);
    CircleShape1.setFillColor(sf::Color::Red);
    CircleShape1.setOutlineColor(sf::Color::Blue);
    CircleShape1.setOrigin(sf::Vector2f(radius, radius));
    CircleShape1.setPosition(position);
}


void Particle::Push(const sf::Vector2f delta_velocity)
{
    velocity_ += delta_velocity;
}


void Particle::Update(const float dt)
{
    position_ += velocity_ * dt;
    velocity_ += acceleration_ * dt;

    //Обработка столкновений, из HandleCollisions:

    if (position_.x < radius_)
    {
        position_.x = radius_;
        velocity_.x = -velocity_.x / 2.0f;
    }

    if (position_.x + radius_ > WINDOW_SIZES.x)
    {
        position_.x = WINDOW_SIZES.x - radius_;
        velocity_.x = -velocity_.x / 2.0f;
    }

    if (position_.y < radius_)
    {
        position_.y = radius_;
        velocity_.y = -velocity_.y / 2.0f;
    }

    const float bottom_gap = 50.0f;
    if (position_.y + radius_ + bottom_gap > WINDOW_SIZES.y)
    {
        position_.y = WINDOW_SIZES.y - radius_ - bottom_gap;
        velocity_.y = -velocity_.y / 2.0f;
    }
}


void Particle::Render(sf::RenderWindow& window)
{
    CircleShape1.setPosition(position_);
    CircleShape1.setRadius(radius_);

    window.draw(CircleShape1);
}


ParticleSystem::ParticleID ParticleSystem::AddParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float radius)
{
    Particle new_particle(position, velocity, acceleration, radius);
    particles_.push_back(new_particle);
    return particles_.size();
}


void ParticleSystem::RemoveParticle(const ParticleID particle_id)
{
  
    particles_.erase(particles_.begin() + particle_id);
}


const Particle& ParticleSystem::GetParticleByID(const ParticleID particle_id)
{
    return particles_[particle_id];
}


void ParticleSystem::Render(sf::RenderWindow& window)
{
    for (int i = 0; i < particles_.size(); i++)
    {
        particles_[i].Render(window);
    }
}


void ParticleSystem::Update(const float dt)
{
    for (int i = 0; i < particles_.size(); i++)
    {
        particles_[i].Update(dt);
    }
}


void ParticleSystem::Push(const sf::Vector2f delta_velocity)
{
    for (int i = 0; i < particles_.size(); i++)
    {
        particles_[i].Push(delta_velocity);
    }
}