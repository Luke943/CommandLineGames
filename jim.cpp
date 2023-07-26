// Text adventure

#include <iostream>

int getChoice(int max);

int main()
{
    int choice{};
    std::cout << "###############################\n";
    std::cout << "### JIM'S FISHING ADVENTURE ###\n";
    std::cout << "###############################\n\n";

    std::cout << "Hello there. Want to hear a story about Jim fishing?\n\n";
    std::cout << "1) Yes, sounds exiting!\n";
    std::cout << "2) Why not...\n";
    std::cout << "3) Not really.\n";

    choice = getChoice(3);
    std::cout << "\n";

    if (choice == 1)
    {
        std::cout << "Great! Let's begin...\n";
    }
    else if (choice == 2)
    {
        std::cout << "Wow, really excited aren't you.\n";
        std::cout << "Anyway, let's begin...\n";
    }
    else
    {
        std::cout << "How ungreatful! Bye.\n";
        return 0;
    }

    std::cout << "It was a sunny day at the lake and Jim was out fishing on his boat.\n";
    std::cout << "It was so exciting that he fell asleep!\n";
    std::cout << "zzz\n";
    std::cout << "zzzzzz\n";
    std::cout << "zzzzzzzzzz\n";

    std::cout << "This isn't going anywhere. What shall we do about it?\n\n";
    std::cout << "1) Wake Jim up.\n";
    std::cout << "2) Let Jim sleep.\n";

    choice = getChoice(2);
    std::cout << "\n";

    if (choice == 1)
    {
        std::cout << "Pretty rude, but this is on you.\n";
    }
    else
    {
        std::cout << "Yes it's all so peaceful...\n";
        std::cout << "zzz\n";
        std::cout << "zzzzzz\n";
        std::cout << "zzzzzzzzzz\n";
        std::cout << "Maybe we really should wake him up?\n\n";

        std::cout << "1) Wake Jim up.\n";
        std::cout << "2) Let Jim sleep.\n";

        choice = getChoice(2);
        std::cout << "\n";

        if (choice == 1)
        {
            std::cout << "Ha! I knew you would.\n";
        }
        else
        {
            std::cout << "zzz\n";
            std::cout << "zzzzzz\n";
            std::cout << "zzzzzzzzzz\n";
            std::cout << "Beautiful nap time...\n";
            goto end;
        }
    }

    std::cout << "A mysterious force gives Jim a huge shove.\n";
    std::cout << "'AHH!', yells Jim.\n";
    std::cout << "Uh oh, that was a bit much.\n";
    std::cout << "Still half asleep, Jim tumbles over the side of his boat into the lake!\n";

    std::cout << "Can Jim swim?\n\n";

    std::cout << "1) Yes!\n";
    std::cout << "2) Nope.\n";
    std::cout << "3) Isn't this your story?\n";

    choice = getChoice(3);
    std::cout << "\n";

    if (choice == 3)
    {
        std::cout << "I suppose it is...\n";
        std::cout << "Erm...............\n";
        std::cout << "I procrastinated too long! Jim can't swim!\n\n";
        choice = 2;
    }

    if (choice == 1)
    {
        std::cout << "Phwew, that's a relief.\n";
        std::cout << "Jim spashes around a bit before climbing back into his boat.\n";
        std::cout << "Luckily, it's a warm day so he'll dry off quickly.\n";
        std::cout << "He let's out a chuckle about the whole thing and decides it's time to row back to shore.\n";
        goto end;
    }
    else if (choice == 2)
    {
        std::cout << "Jim     can't     swim !     PANIC ! ! !\n\n";
        std::cout << "1) Panic!\n";
        std::cout << "2) How deep is the water?\n";
        std::cout << "3) He can't swim... but he can fly!\n";

        choice = getChoice(3);
        std::cout << "\n";

        if (choice == 1)
        {
            std::cout << "Splash, splash, splash.\n";
            std::cout << "Glug, glug, glug.\n";
            std::cout << "Jim goes under, never to be seen again...\n";
            std::cout << ":(\n";
            std::cout << "What have we done?!\n";
            std::cout << "Let's never speak about this again!\n";
            return 0;
        }
        else if (choice == 2)
        {
            std::cout << "Oh right. The water is only waist high!\n";
            std::cout << "What a relief.\n";
            std::cout << "Still a little startled, Jim stands up and climbs back into his boat.\n";
            std::cout << "'Time to go home', he thinks.\n";
        }
        else
        {
            std::cout << "He can??? Erm...\n";
            std::cout << "Wooosh. Jim flies away!\n";
        }
    }

end:
    std::cout << "\nAnd with that, our delightful story comes to an end.\n";
    std::cout << "Goodbye!\n";
    return 0;
}

int getChoice(int max)
{
    char input{};
    for (int i = 0; i < 3; i++)
    {
        std::cin >> input;
        int x = input - '0';
        if (x >= 1 && x <= max)
            return x;
        else
        {
            std::cout << "That's not a valid choice. Try again... ";
        }
    }
    std::cout << "\nI give up. No more story!\n";
    exit(0);
}
