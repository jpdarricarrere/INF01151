#include "server_message.h"
#include "../libs/jsoncpp/json/json.h"

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

std::string ServerMessageData::serialize()
{
    Json::FastWriter fastWriter;
    Json::Value server_message;

    server_message["id"] = this->id;
    server_message["type"] = this->msg_type;

    switch (this->msg_type)
    {
    case ServerMsgType::LoginFail:
    case ServerMsgType::LoginSuccess:
    {
        break; // No payload.
    }
    case ServerMsgType::ServerSendCommand:
    {
        server_message["username"] = this->payload.message.username;
        server_message["body"] = this->payload.message.body;
        break;
    }

    case ServerMsgType::FollowCommandFail:
    case ServerMsgType::FollowCommandSuccess:
    {
        server_message["username"] = this->payload.username;
        break;
    }
    default:
    {
#ifdef DEBUG
        cout << "ServerMessageData::serialize() used for unimplemented ServerMsgType: " << this->msg_type << endl
             << endl;
#endif
        break;
    }
    }

    std::string json = fastWriter.write(server_message);
    return json;
}
