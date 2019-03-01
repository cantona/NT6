// sanyin.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sanyin"; }

string chinese_name() { return "三陰蜈蚣爪之毒"; }

string update_msg_others()
{
       return "$N突然渾身不住的抖動，看上去十分痛苦。\n";
}

string update_msg_self()
{
        return HIB "忽然你覺得四肢百賅是似乎有無數小蟲在遊走，麻癢難忍！\n" NOR;
}

