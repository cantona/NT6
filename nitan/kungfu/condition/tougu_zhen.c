#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "tougu_zhen"; }

string chinese_name() { return "透骨寒針之擾"; }

string update_msg_others()
{
       return HIC "$N只覺一股奇寒散盡七筋八脈，猶感身陷萬蟻之獄，全身不停的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIC "你感到一股切骨奇寒由傷口處升起，看來是中了透骨針內勁的幹擾！\n" NOR;
}

