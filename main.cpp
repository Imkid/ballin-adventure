#include <SFML/Graphics.hpp>
#include "header_files/Collider.hpp"
#include "header_files/Fireball.hpp"
#include "header_files/Hero.hpp"
#include "header_files/Mario.hpp"
#include "header_files/Sewer.hpp"
#include <iostream>

// test

int main()
{
//{     setup:  create window, sprites/images, and variables

    // Create the main window
    sf::RenderWindow App(sf::VideoMode(930, 851), "moreobjgoomba");

    // Load image for collider sprites
    sf::Image spritesImage;
    if (!spritesImage.LoadFromFile("images/spritesSheet.bmp"))
        return EXIT_FAILURE;

    // load image for background
    sf::Image bgImage;
    if (!bgImage.LoadFromFile("images/background.bmp"))
        return EXIT_FAILURE;

    // make bgImage into bgSprite
    sf::Sprite bgSprite(bgImage);

    // initialize some variables
    const int NUM_MARIOS = 3, NUM_FIREBALLS = 6, NUM_SEWERS = 0;
    int i = 0; // counter variable
    sf::Clock jumpClock;

    // create hero sprite
    sf::Sprite heroSprite(spritesImage);
    cHero theHero(heroSprite);

    // create arrays of pointers to sprites, then create new sprites in each index
    sf::Sprite * fireballSpritesArray[NUM_FIREBALLS];
    for (i = 0; i < NUM_FIREBALLS; i++) {
        fireballSpritesArray[i] = new sf::Sprite(spritesImage);
        fireballSpritesArray[i]->SetSubRect(sf::IntRect(4, 108, 35, 139));
        fireballSpritesArray[i]->SetCenter(0, 31);
        fireballSpritesArray[i]->SetX(30 * i);
        fireballSpritesArray[i]->SetY(650);
    }

    sf::Sprite * marioSpritesArray[NUM_MARIOS];
    for (i = 0; i < NUM_MARIOS; i++) {
        marioSpritesArray[i] = new sf::Sprite(spritesImage);
        marioSpritesArray[i]->SetSubRect(sf::IntRect(4, 180, 67, 307));
        marioSpritesArray[i]->SetCenter(0, 126);
        marioSpritesArray[i]->SetX(10 * i);
        marioSpritesArray[i]->SetY(762);
    }

    sf::Sprite * sewerSpritesArray[NUM_SEWERS];
    for (i = 0; i < NUM_SEWERS; i++) {
        sewerSpritesArray[i] = new sf::Sprite(spritesImage);
        sewerSpritesArray[i]->SetSubRect(sf::IntRect(104, 4, 231, 191));
        sewerSpritesArray[i]->SetCenter(0, 187);
        sewerSpritesArray[i]->SetY(762);
    }

    // manually setting x-values of sewers (for now)
//    sewerSpritesArray[0]->SetX(127);
//    sewerSpritesArray[1]->SetX(750);


    cMario marioArray[NUM_MARIOS];
    cFireball fireballArray[NUM_FIREBALLS];
    cSewer sewerArray[NUM_SEWERS];
//}

	// Start the game loop
    while (App.IsOpened())
    {
        //{ Process events
        sf::Event anEvent;
        while (App.GetEvent(anEvent))
        {
            // Close window : exit
            if (anEvent.Type == sf::Event::Closed)
                App.Close();

            // press escape : exit
            if (anEvent.Type == sf::Event::KeyPressed && anEvent.Key.Code == sf::Key::Escape)
                App.Close();

            if (anEvent.Type == sf::Event::KeyPressed && anEvent.Key.Code == sf::Key::Space) {
                heroSprite.SetX(100);
                heroSprite.SetY(100);
                theHero.stopMotion();
            }
        }
        //}

        //{ get positions of colliders and resolve collisions
        theHero.getCoordinates(heroSprite);

        for (i = 0; i < NUM_MARIOS; i++) {
            marioArray[i].getCoordinates(*marioSpritesArray[i]);
            if (theHero.checkCollisions(marioArray[i])) {
                // TODO mario/goomba collision
                marioArray[i].setIsDead(true);

            }
        }

        for (i = 0; i < NUM_FIREBALLS; i++) {
            fireballArray[i].getCoordinates(*fireballSpritesArray[i]);
            if (theHero.checkCollisions(fireballArray[i])) {
                // TODO fireball/goomba collision
                // std::cout << "fireball colliding...\n";
            }
        }


        for (i = 0; i < NUM_SEWERS; i++) {
            sewerArray[i].getCoordinates(*sewerSpritesArray[i]);
            if (theHero.checkCollisions(sewerArray[i])) {
                // TODO sewer/goomba collision
                std::cout << "sewer colliding...\n";
            }
        }
            //std::cout << theHero.getMaxY() << std::endl;


//}

        //{ perform movement and draw sprites in same loop
        //  (might not be able to do this (movement, then collisions, then drawing))

        // Clear screen, draw background
        App.Clear();
        App.Draw(bgSprite);

        for (i = 0; i < NUM_SEWERS; i++) {
            App.Draw(*sewerSpritesArray[i]);
        }

        for (i = 0; i < NUM_MARIOS; i++) {
            if (marioArray[i].getIsDead())
                marioArray[i].reset(*marioSpritesArray[i]);
            else {
                marioSpritesArray[i]->Move(marioArray[i].getMovement());
            }
            App.Draw(*marioSpritesArray[i]);
        }

        // process input
        const sf::Input& theInput = App.GetInput();
        heroSprite.Move(theHero.getMovement(theInput, jumpClock));
        App.Draw(heroSprite);

        for (i = 0; i < NUM_FIREBALLS; i++) {
            fireballSpritesArray[i]->Move(fireballArray[i].getMovement());
            App.Draw(*fireballSpritesArray[i]);
        }

//        fireballArray[i].spritePtr.Move(fireballArray[i].getMovement());

        // Update the window
        App.Display();
        //std::cout << "x: " << theHero.getMinX() << std::endl << "y: " << theHero.getMaxY() << std::endl;
//}
    }

//{ deallocate memory
    for (i = 0; i < NUM_FIREBALLS; i++)
        delete fireballSpritesArray[i];

    for (i = 0; i < NUM_MARIOS; i++)
        delete marioSpritesArray[i];

    for (i = 0; i < NUM_SEWERS; i++)
        delete sewerSpritesArray[i];
//}

    return EXIT_SUCCESS;
}

