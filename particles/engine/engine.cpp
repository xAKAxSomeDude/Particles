#include "Engine.h"

Engine::Engine()
{
//    Call create on m_Window to populate the RenderWindow member variable
//    You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution
    m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Fireworks", Style::Default);
}
void Engine::run()

{
//    Construct a local Clock object to track Time per frame
//    The time differential (dt) since the last frame will be passed into update
        Clock localClock;
        Time df = localClock.restart();


//    Construct a local Particle to be used for the unit tests.  The tests will be given to you, and you can use them to check your progress as you go.  Use the following code exactly:
        cout << "Starting Particle unit tests..." << endl;
        sf::Vector2i mouseClickPosition(static_cast<int>(m_Window.getSize().x) / 2, static_cast<int>(m_Window.getSize().y) / 2);
        Particle testP(m_Window, 4, mouseClickPosition);

        testP.unitTests();
        cout << "Unit tests complete. Starting engine..." << endl;

//    After the unit tests are complete, create your game loop
        localClock.restart();
    /*Loop*/ while (m_Window.isOpen())
        {
            //Convert the clock time to seconds
            df = localClock.getElapsedTime();
            //Call input
            input();
            //Call update
            update(df.asSeconds());
            //Call draw
            draw();
            //Restart the clock (this will return the time elapsed since the last frame)
            localClock.restart();
        }
}
void Engine::input()
{
    Event event;
    // Poll the Windows event queue
    {
        while (m_Window.pollEvent(event))
        {
            //        Handle the Escape key pressed and closed events so your program can exit
            if (event.type == Event::Closed)
            {
                cout << "Window closed with close button" << endl;
                m_Window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    cout << "Escape key used to close program" << endl;
                    m_Window.close();
                }
            if (event.type == Event::MouseButtonPressed)
            {
//             Handle the left mouse button pressed event
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2f mouseLocation = static_cast<Vector2f>(Mouse::getPosition(m_Window));
//                   Create a loop to construct 5 particles (I used 5, you can change this if you want)
                    int numPart = rand() % 10;
                    for (size_t i = 0; i < static_cast<unsigned long long>(numPart); i++)
                    {
//                    The numPoints parameter in the Particle constructor is a random number in the range [25:50]
                        int numPoints = 25 + rand() % 26;

//                      Pass the position of the mouse click into the Particle constructor so it has a starting position
                        Particle newPart(m_Window, numPoints, static_cast<Vector2i>(mouseLocation));
                        m_particles.push_back(newPart);
                    }
                }
            }

        }
    }
}
void Engine::update(float dtAsSeconds)
{
//The general idea here is to loop through m_particles and call update on each Particle in the vector whose ttl (time to live) has not expired
    for (size_t i = 0; i < m_particles.size();)
    {
        //int removalCount = 0;
//      //  If a particle's ttl has expired, it must be erased from the vector
        //if (m_particles[i-removalCount].getTTL < 0.00)
        //{
        //    m_particles.erase(m_particles.begin+i-removalCount);
        //    removalCount++;
        //}
        
//    This is best done with an iterator-based for-loop
//        Don't automatically increment the iterator for each iteration
        if (m_particles[i].getTTL() > 0.0)
        {
//            Call update on that Particle
            m_particles[i].update(dtAsSeconds);
//                Pass in the time differential since the last frame (dt)
//            increment the iterator
            i++;
        } else if (m_particles[i].getTTL() <= 0)
            {
//            erase the element the iterator points to
                m_particles.erase(m_particles.begin() + i);
                cout << "Particle Deleted." << endl;
//            erase returns an iterator that points to the next element after deletion, or end if it is the end of the vector
//                Assign the iterator to this return value
//            Do not increment the iterator (if you do you might increment past the end of the vector after you delete the last element)
            }
    }
}
void Engine::draw()
{
//    clear the window
        m_Window.clear();
//    Loop through each Particle in m_Particles
        for (const auto& particle : m_particles)
        {
//        Pass each element into m_Window.draw()
            m_Window.draw(particle);
//        Note:  This will use polymorphism to call your Particle::draw() function
        }
        //    display the window
        m_Window.display();
}