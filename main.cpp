#include <iostream>
// #include <string>

int main()
{
    const int rows    = 4;
    const int columns = 3;

    int currentState = 0;
    int inSignal     = 0;

    enum States
    {
        IDLE,
        OPEN,
        HANDLING
    };

    int nextStates[rows][columns] = { { OPEN, OPEN, HANDLING },
                                      { IDLE, HANDLING, HANDLING },
                                      { IDLE, HANDLING, IDLE },
                                      { IDLE, IDLE, IDLE } };

    std::string outputSignals[rows][columns]
        = { { "TCP. Connected", "TCP. Already connected", "TCP. Already connected" },
            { "HTTP. No connection",
              "HTTP. Request recieved, handling",
              "HTTP. Request recieved, setting in queue" },
            { "HTTP. No connection",
              "HTTP. Request handled, sending",
              "HTTP. Answer sent, waiting TCP-connection" },
            { "TCP. Waiting", "TCP. Closed, waiting", "TCP. Closed, waiting" } };

    std::string stateNames[rows]
        = { "TCP. Waiting connection", "TCP. Connection opened", "HTTP. Handling" };

    std::cout << "Current state: " << currentState << " - " << stateNames[currentState] << "\n\n";
    std::cout
        << "Input signals:\n 0 - [TCP. Connection requested];\n 1 - [HTTP. Recieved];\n 2 - [HTTP. Handled];\n 3 - [TCP.Connection interrupted];\n 4 - Show hint;\n 5 - Exit program. \n\n";

    while (1)
    {
        std::cout << "Signal:";
        std::cin >> inSignal;
        std::cout << "\n";

        if ((inSignal < 4) && (inSignal >= 0))
        {
            currentState = nextStates[inSignal][currentState];

            std::cout << "Current state: " << currentState << " - " << stateNames[currentState]
                      << std::endl;
            std::cout << "Output signal: [" << outputSignals[inSignal][currentState] << "]\n\n";
        }
        else if (4)
        {
            std::cout << "Current state: " << currentState << " - " << stateNames[currentState]
                      << "\n\n";
            std::cout
                << "Input signals: 0 - [TCP. Connection requested]; 1 - [HTTP. Recieved]; 2 - [HTTP. Handled]; 3 - [TCP.Connection interrupted]; 4 - Show hint; 5 - Exit program. \n\n";
        }

        else if (5)
        {
            std::cout << "Exiting program \n\n";
            return 0;
        }

        else
        {
            std::cout << "Unknown input signal \n\n";
            break;
        }
    }
    return 0;
}