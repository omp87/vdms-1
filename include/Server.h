#pragma once

#include <csignal>

#include "jarvis.h"
#include "util.h"

#include "QueryHandler.h"
#include "CommunicationManager.h"

namespace athena {
    class Server
    {
        static const int SERVER_PORT = 55555;
        static const int QUERY_BUFFER_SIZE = 4096;  // in bytes

        CommunicationManager *_cm;

        // TODO: Partitioner here

        // Aux lock, not in use
        std::mutex *_dblock;

        // Handle ^c
        static bool shutdown;
        int install_handler();
        static void sighandler(int signo)
            { Server::shutdown = (signo == SIGINT); }

    public:
        Server();
        void process_requests();
        ~Server();
    };
};