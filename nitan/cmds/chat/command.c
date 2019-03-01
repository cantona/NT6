// command.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object me, mapping info)
{
        string msg;
        seteuid(geteuid());

        if (! is_root(previous_object()))
                return 0;

        if (! info[ARG])
                return 1;

        if (! environment(me) ||
            environment(me) == find_object(VOID_OB))
                return MESSAGE_D->error_msg("你現在還在縹緲的虛空中，沒什麼好做的。\n");

        // clear the error
        if (! me->force_me(info[ARG]))
                return MESSAGE_D->error_msg(query_temp("notify_fail", me));

        return 1;
}
