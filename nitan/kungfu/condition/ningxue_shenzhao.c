#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ningxue_shenzhao"; }

string chinese_name() { return "凝血之擾"; }

string update_msg_others()
{
       return HIR "$N" HIR "只感內息頓滯，“哇”的一聲噴出一大口鮮血。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只感內息頓滯，全身血液竟漸漸的開始凝固起來！\n" NOR;
}

