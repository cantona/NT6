// corpse_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "corpse_poison"; }

string chinese_name() { return "腐屍毒"; }

string update_msg_others()
{
        return WHT "$N" WHT "全身上下淌著黃水，不住的嘶嚎，散發"
               "出陣陣極難聞的惡臭。\n" NOR;
}

string update_msg_self()
{
        return WHT "你只覺全身肌膚便似腐爛了一般，散發出一股極難"
               "聞的惡臭。\n" NOR;
}

string die_msg_others()
{
        return WHT "$N" WHT "嘶嚎了幾聲，就再沒半點動靜，全身散"
               "發出一股惡臭。\n" NOR;
}

string die_reason()
{
        return "腐屍毒發作生亡了";
}