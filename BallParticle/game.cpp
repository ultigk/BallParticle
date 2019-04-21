#include "game.h"
#include "window.h"
#include <SFML/Graphics.hpp>

extern const sf::Vector2u WINDOW_SIZES(800, 600);

Game::Game()
    : main_window_("Several ballz", WINDOW_SIZES) // больше не передаем в Game-конструктор particle_ с заданными коор-ами
{
    const auto particle1_id = particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 2.0f, WINDOW_SIZES.y / 2.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 10.0f),
        25.0f);

    const auto particle2_id = particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 3.0f, WINDOW_SIZES.y / 3.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 10.0f),
        50.0f);
  
    const auto particle3_id = particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 4.0f, WINDOW_SIZES.y / 4.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 10.0f),
        75.0f);
}


void Game::Run()
{
    const float updatets_per_seconds = 60.0f;
    const sf::Time time_per_update = sf::seconds(1.0f / updatets_per_seconds);

    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;

    while (!main_window_.CheckIsDone())
    {
        time_since_last_update += clock.restart();

        while (time_since_last_update >= time_per_update)
        {
            HandleInput();
            Update(time_per_update.asSeconds());
            time_since_last_update -= time_per_update;
        }
        //Update();
        Render();
    }
}


void Game::HandleInput()
{
    sf::Vector2f increment(0, 0);
    const float delta = 1.5f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        increment.y -= delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        increment.x += delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        increment.y += delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        increment.x -= delta;
    }

    particles_.Push(increment);
}


void Game::Update(const float dt)
{
    main_window_.Update(dt);
    particles_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();
    /*main_window_.Draw(particles_);
    метод Render должен отрисовать несколько частиц
    particles_ - приватная переменная класса ParticleSystem*/

    //particles_.Render(window);
    particles_.Render(main_window_.GetWindow());
    main_window_.EndDraw();
}