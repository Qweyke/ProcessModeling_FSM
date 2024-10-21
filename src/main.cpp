#include <iostream>
#include <string>

constexpr uint16_t ROWS          = 4;
constexpr uint16_t COLUMNS       = 3;
constexpr uint16_t INPUT_SIGNALS = 4;

uint16_t currentState = 0;
uint16_t inSignal     = 0;

enum States
{
    IDLE,
    OPEN,
    HANDLING
};

uint16_t nextStates[ROWS][COLUMNS] = { { OPEN, OPEN, HANDLING },
                                       { IDLE, HANDLING, HANDLING },
                                       { IDLE, HANDLING, IDLE },
                                       { IDLE, IDLE, IDLE } };

std::string outputSignals[ROWS][COLUMNS]
    = { { "TCP. Connected", "TCP. Already connected", "TCP. Already connected" },
        { "HTTP. No connection",
          "HTTP. Request recieved, handling",
          "HTTP. Request recieved, setting in queue" },
        { "HTTP. No connection",
          "HTTP. Request handled, sending",
          "HTTP. Answer sent, waiting TCP-connection" },
        { "TCP. Waiting", "TCP. Closed, waiting", "TCP. Closed, waiting" } };

std::string inputSignals[INPUT_SIGNALS] = { "[TCP. Connection requested]",
                                            "[HTTP. Recieved]",
                                            "[HTTP. Handled]",
                                            "[TCP.Connection interrupted]" };

std::string states[ROWS]
    = { "TCP. Waiting connection", "TCP. Connection opened", "HTTP. Handling" };


void displaySignals(std::string signals[], size_t size)
{
    std::string output;
    output.reserve(size * 40);
    std::cout << "Input signals:\n";

    int i = 0;
    for (i; i < size; i++)
    {
        output += std::to_string(i) + " - " + (signals[i]) + (";\n");
    }

    output += (std::to_string(i)) + " - Show hint;\n" + (std::to_string(i + 1))
              + " - Exit program. \n\n";
    std::cout << output;
}


int main()
{
    std::cout << "Current state: " << currentState << " - " << states[currentState] << "\n\n";
    displaySignals(inputSignals, INPUT_SIGNALS);

    while (1)
    {
        std::cout << "Signal:";
        std::cin >> inSignal;
        std::cout << "\n";
        if ((inSignal < 4) && (inSignal >= 0))
        {
            currentState = nextStates[inSignal][currentState];

            std::cout << "Current state: " << currentState << " - " << states[currentState]
                      << std::endl;
            std::cout << "Output signal: [" << outputSignals[inSignal][currentState] << "]\n\n";
        }
        else if (4)
        {
            std::cout << "Current state: " << currentState << " - " << states[currentState]
                      << "\n\n";
            displaySignals(inputSignals, INPUT_SIGNALS);
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