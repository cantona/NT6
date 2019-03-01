//ice_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "snake_poison"; }

string chinese_name() { return "蛇毒"; }

string update_msg_others()
{
       return HIB "$N的身子突然晃了兩晃，顯得很痛苦的樣子。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然一陣刺痛，你感覺毒性正在慢慢侵入你的身體！\n" NOR;
}
