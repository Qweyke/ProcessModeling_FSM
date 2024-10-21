#include <iostream>
#include <string>

constexpr uint16_t STATES        = 4;
constexpr uint16_t INPUT_SIGNALS = 3;

// output signals display
constexpr const char* TCP_OPENING            = "[TCP: Opening connection]";
constexpr const char* TCP_CONNECTED          = "[TCP: Already connected]";
constexpr const char* TCP_DISCONNECTED       = "[TCP: No connection]";
constexpr const char* HTTP_REQ_RECEIVED      = "[HTTP: Request recieved, handling]";
constexpr const char* HTTP_NEXT_REQ_RECEIVED = "[HTTP: Next request received, setting in queue]";
constexpr const char* HTTP_RESP_READY        = "[HTTP: Response ready, waiting sending to begin]";
constexpr const char* HTTP_RESP_SEND_PREP    = "[HTTP: Request handled, preparing to send]";
constexpr const char* HTTP_RESP_SENDING      = "[HTTP: Sending response]";

// input signals display
constexpr const char* INP_TCP_CONECT = "(TCP: Connection request)";
constexpr const char* INP_HTTP_RECVD = "(HTTP: Request recieved)";
constexpr const char* INP_HTTP_READY = "(HTTP: Response ready)";

// states display
constexpr const char* ST_IDLE     = "{TCP: Waiting connection}";
constexpr const char* ST_OPEN     = "{TCP: Connection opened}";
constexpr const char* ST_HANDLING = "{HTTP: Handling request}";
constexpr const char* ST_SENDING  = "{HTTP: Sending response}";

enum States
{
    IDLE,
    OPEN,
    HANDLING,
    SENDING
};

uint16_t nextStates[INPUT_SIGNALS][STATES] = {
    { OPEN, OPEN, HANDLING, SENDING },
    { IDLE, HANDLING, HANDLING, SENDING },
    { IDLE, SENDING, SENDING, IDLE },
};

std::string outputSignals[INPUT_SIGNALS][STATES]
    = { { TCP_OPENING, TCP_CONNECTED, TCP_CONNECTED, TCP_CONNECTED },
        { TCP_DISCONNECTED, HTTP_REQ_RECEIVED, HTTP_NEXT_REQ_RECEIVED, HTTP_NEXT_REQ_RECEIVED },
        { TCP_DISCONNECTED, HTTP_RESP_READY, HTTP_RESP_SEND_PREP, HTTP_RESP_SENDING } };

std::string inputSignals[INPUT_SIGNALS] = { INP_TCP_CONECT, INP_HTTP_RECVD, INP_HTTP_READY };

std::string nextStatesText[STATES] = { ST_OPEN, ST_HANDLING, ST_SENDING, ST_IDLE };


void static displaySignals(std::string signals[], size_t size)
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
    uint16_t currentState = 0;
    uint16_t inSignal     = 0;


    std::cout << "Current state: " << currentState << " - " << nextStatesText[currentState]
              << "\n\n";
    displaySignals(inputSignals, INPUT_SIGNALS);

    while (1)
    {
        std::cout << "Signal:";
        std::cin >> inSignal;
        std::cout << "\n";
        if ((inSignal < INPUT_SIGNALS) && (inSignal >= 0))
        {
            std::cout << "Output signal: " << outputSignals[inSignal][currentState] << "\n";

            currentState = nextStates[inSignal][currentState];

            std::cout << "Current state: " << currentState << " - " << nextStatesText[currentState]
                      << std::endl
                      << std::endl;
        }
        else if (INPUT_SIGNALS)
        {
            std::cout << "Current state: " << currentState << " - " << nextStatesText[currentState]
                      << "\n\n";
            displaySignals(inputSignals, INPUT_SIGNALS);
        }

        else if (INPUT_SIGNALS + 1)
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