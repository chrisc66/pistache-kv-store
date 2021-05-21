#include <atomic>

#include <pistache/client.h>
#include <pistache/http.h>
#include <pistache/net.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void getToken(const std::string & str, std::vector<std::string> & tokens){
    std::stringstream ss; 
    ss.str(str);

    std::string tmp; 
    while(ss >> tmp){
        tokens.push_back(tmp);
    }
}

void printToken(const std::vector<std::string> & tokens){
    for (int i = 0; i < tokens.size(); i ++)
        std::cout << tokens[i] << " ";
    std::cout << std::endl;
}

void printPrompt(){ std::cout << "> "; }

void printUserMessage(const std::string & msg){ std::cout << msg << std::endl; }

void printErrorMessage(const std::string & msg){ std::cout << "Error: " << msg << std::endl; }

void printHelp(){
    std::cout << "Avaliable commands are: " << std::endl;
    std::cout << "  put <key> <value>" << std::endl;
    std::cout << "  get <key>" << std::endl;
    std::cout << "  delete <key>" << std::endl;
    std::cout << "  quit | exit" << std::endl;
    std::cout << "  help | usage" << std::endl;
}

void handleCommand(const std::vector<std::string> & tokens, bool & running){
    if (tokens.size() == 0){
        printUserMessage("Unrecognized argument, please enter again.");
    }
    else if (tokens[0] == "put"){
        if (tokens.size() != 3){
            printErrorMessage("Invalid number of arguments, \"put\" expects exactly two arguments.");
        }
        else{
            printUserMessage("Received: put " + tokens[1] + " "+ tokens[2]);
            // TODO send put message
        }
    }
    else if (tokens[0] == "get"){
        if (tokens.size() != 2){
            printErrorMessage("Invalid number of arguments, \"get\" expects exactly one arguments");
        }
        else{
            printUserMessage("Received: get " + tokens[1]);
            // TODO send put message
        }
    }
    else if (tokens[0] == "delete"){
        if (tokens.size() != 2){
            printErrorMessage("Invalid number of arguments, \"delete\" expects exactly one arguments");
        }
        else{
            printUserMessage("Received: delete " + tokens[1]);
            // TODO send delete message
        }
    }
    else if (tokens[0] == "quit" || tokens[0] == "exit"){
        running = false;
        printUserMessage("Exiting the application...");
    }
    else if (tokens[0] == "help" || tokens[0] == "usage"){
        printHelp();
    }
    else {
        printUserMessage("Unrecognized argument, please enter again.");
    }
}

int main(int argc, char* argv[]){
    Pistache::Http::Client client;
    auto opts = Pistache::Http::Client::options().threads(1).maxConnectionsPerHost(8);
    client.init(opts);

    bool running = true;
    while (running){
        printPrompt();

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> tokens; 
        getToken(input, tokens);
        
        handleCommand(tokens, running);
    }

    client.shutdown();
}
