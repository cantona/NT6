#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yinfeng_dao"; }

string chinese_name() { return "陰風刮骨之擾"; }

string update_msg_others()
{
       return HIW "$N慘嚎一聲，只覺全身肌肉就像要撕裂開一般，豆大的汗珠不住的滴下。\n" NOR;
}

string update_msg_self()
{
        return HIW "你感到一股切骨奇寒由傷口處升起，看來是中了陰風刀內勁的幹擾！\n" NOR;
}

