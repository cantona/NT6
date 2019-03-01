#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "zhurong_jian"; }

string chinese_name() { return "烈炎劍氣"; }

string update_msg_others()
{
       return HIR "$N" HIR "一聲慘嚎，劍傷處竟猶如被烈火灼燒過一般！\n" NOR;
}

string update_msg_self()
{
        return HIR "你感到一股錐心的灼痛從劍傷處傳來，血液竟似要沸騰了起來！\n" NOR;
}

