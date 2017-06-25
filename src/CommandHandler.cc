
#include "CommandHandler.h"

using namespace athena;

CommandHandler::CommandHandler(comm::Connection* conn):
		_conn(conn)
{
	assert(_conn != NULL);

	// We throw, we need to define exceptions model
}

protobufs::queryMessage CommandHandler::get_command()
{
	std::basic_string<uint8_t> msg = _conn->recv_message();

	protobufs::queryMessage cmd;
	cmd.ParseFromArray((const void*)msg.data(), msg.length());

	return cmd;
}

void CommandHandler::send_response(protobufs::queryMessage cmd)
{
	std::basic_string<uint8_t> msg(cmd.ByteSize(),0);
	cmd.SerializeToArray((void*)msg.data(), msg.length());
	_conn->send_message(msg.data(), msg.length());
}