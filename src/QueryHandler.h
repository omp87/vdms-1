#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>

#include "PMGDQueryHandler.h" // to provide the database connection
#include "RSCommand.h"
#include "comm/Connection.h"

// Json parsing files
#include <jsoncpp/json/value.h>

namespace athena {

typedef ::google::protobuf::RepeatedPtrField<std::string> BlobArray;

    // Instance created per worker thread to handle all transactions on a given
    // connection.
    class QueryHandler
    {
        friend class QueryHandlerTester;

        PMGDQueryHandler _pmgd_qh;
        std::unordered_map<std::string, RSCommand *> _rs_cmds;

        bool syntax_checker(const Json::Value &root, Json::Value& error);
        int parse_commands(const std::string& commands, Json::Value& root);
        void process_query(protobufs::queryMessage& proto_query,
                           protobufs::queryMessage& response);

    public:
        QueryHandler(Jarvis::Graph *db, std::mutex *mtx);
        ~QueryHandler();

        void process_connection(comm::Connection *c);
    };
};
