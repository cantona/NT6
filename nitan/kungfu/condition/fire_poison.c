// fire_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "fire_poison"; }

string chinese_name() { return "星宿毒燄"; }

string update_msg_others()
{
        return HIR "$N" HIR "一聲慘嚎，全身竟燃起了" HIG "碧綠色"
               HIR "的火燄。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只覺全身灼熱無比，身體上燃起的" HIG "碧燄"
               HIR "直焚心髓。\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "焦枯的身子在地上撲騰了幾下，就再沒"
               "半點動靜了。\n" NOR;
}

string die_reason()
{
        return "被星宿毒燄活活燒死了";
}