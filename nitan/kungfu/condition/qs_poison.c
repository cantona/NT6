#include <ansi.h> 
#include <condition.h> 

inherit F_CLEAN_UP; 
inherit POISON; 

string name() { return "qs_poison"; } 
string chinese_name() { return "七傷拳內傷"; } 

string update_msg_others() 
{
       return HIW "$N" HIW "突然腳下一晃，好像是受了嚴重的內傷！\n" NOR; 
}

string update_msg_self() 
{
       return HIW "你腳下恍惚，精神不能集中，好像是中了陰毒的內傷！\n" NOR; 
}