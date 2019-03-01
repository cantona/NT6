// Code of ShenZhou
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

inherit POISON;

string name() { return "huadu_poison"; }

string chinese_name() { return "星宿蟲毒"; }
string *query_valid_force() 
{ 
        return ({
                "yijinjing",
                "lengyue-shengong",
                "bahuang-gong",
                "beiming-shengong",
                });
}


string update_msg_others()
{
        return HIM "$N" HIB "的目光散亂，神色異常，臉上泛出一層黑氣。\n" NOR;
}

string update_msg_self()
{
        return HIR "你忽然肺腑一陣劇痛，你體內的星宿蟲毒發作了，你覺的這次毒力來的更兇猛！\n" NOR;
}
