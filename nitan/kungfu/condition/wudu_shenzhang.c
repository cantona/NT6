#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "wudu_shenzhang"; }

string chinese_name() { return "噬心毒"; }

string update_msg_others()
{
       return HIR "只見$N" HIR "手按胸口，面色泛黑，痛苦萬分。\n" NOR;
}

string update_msg_self()
{
        return HIB "你忽覺心口疼痛萬分，猶如萬千蟲蟻噬心穿骨！\n" NOR;
}
