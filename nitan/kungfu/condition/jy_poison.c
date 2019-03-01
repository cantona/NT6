#include <ansi.h> 
#include <condition.h> 

inherit F_CLEAN_UP; 
inherit POISON; 

string name() { return "jy_poison"; } 
string chinese_name() { return "九陰白骨爪毒"; } 

string update_msg_others() 
{
       return BLU "$N" BLU "突然只膝彎曲，身子慢慢垂下，口中發出似人似鬼的荷荷之聲。\n" NOR; 
}

string update_msg_self() 
{
       return BLU "你忽然感到身體僵直，已經不聽使喚了。\n" NOR; 
}