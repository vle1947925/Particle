#include "Engine.h"

Engine::Engine()
{
    m_Window.create(sf::VideoMode::getDesktopMode(), "Particles");
}

void Engine::run()
{
    Clock m_Clock;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;


    while (m_Window.isOpen())
    {
        sf::Time dt = m_Clock.restart();
        float dtSeconds = dt.asSeconds();

        input();
        update(dtSeconds);
        draw();
    }
}

void Engine::input()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            m_Window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            for (int i = 0; i < 5; i++)
            {
                int numPoints = rand() % 26 + 25;
                Particle particle(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y });
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        if (it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();
    for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }
    m_Window.display();
}
