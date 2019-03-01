// hyz_damage.c 混元無極勁傷
// by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON; 

string name() { return "hyz_damage"; } 

string chinese_name() { return "混元無極勁內傷"; } 

string update_msg_others() 
{
        return HIW "$N" HIW "的臉色突然大為蒼白，搖搖欲墜，似乎是內傷發作了！\n" NOR; 
}

string update_msg_self() 
{
        return HIW "忽然你一陣頭暈目眩，你所中的混元無極勁內傷發作了！\n" NOR; 
}
