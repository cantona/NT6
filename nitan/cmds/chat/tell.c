// chat command: tell.c

#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object user, mapping info)
{
        if (! stringp(info[MSGTO]))
                return MESSAGE_D->error_msg("你要發消息給誰？\n");

        if (! stringp(info[MESSAGE]))
                return MESSAGE_D->error_msg("你要説什麼話？\n");

        return MESSAGE_D->send_msg_to(user, info[MSGTO], info[MESSAGE]);
}
