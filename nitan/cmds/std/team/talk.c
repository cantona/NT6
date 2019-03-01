// team command: talk

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;

        if (! arg) arg = "...";

        if (! pointerp(t = me->query_team()))
                return notify_fail("你現在並沒有和別人組成隊伍。\n");

        message("team", CYN "【隊伍會話】" + me->name(1) +
                "：" + arg + "\n" NOR, t);
        return 1;
}
