#pragma once

#include <SFML/Graphics.hpp>

using ParticleID = size_t;

class Particle
{
public:
    Particle(sf::Vector2f position_, sf::Vector2f velocity_, sf::Vector2f acceleration_, float radius_);
    virtual ~Particle() = default;

    void Push(const sf::Vector2f increment);
    void Update(const float dt);
    void Render(sf::RenderWindow& window);

    sf::CircleShape CircleShape1;
    sf::CircleShape CircleShape2;

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float radius_;
};

class ParticleSystem
{
public:
    ParticleSystem() = default;
    virtual ~ParticleSystem() = default;
    ParticleID AddParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float radius);
    void RemoveParticle(const ParticleID particle_id);
    const Particle& GetParticleByID(const ParticleID particle_id);

    void Push(const sf::Vector2f delta_velocity);
    void Update(const float dt);
    void Render(sf::RenderWindow& window); //прототип скопировал из аналогичной функции класса Particle
    
private:
    std::vector<Particle> particles_;   
};
