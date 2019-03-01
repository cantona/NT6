#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "cuixin_zhang"; }

string chinese_name() { return "催心掌掌力"; }

string update_msg_others()
{
       return HIR "$N" HIR "一聲慘嚎，內息逆流，“哇”的一聲噴出一大口鮮血。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只感到五臟六腑翻騰不止，劇毒攻心，看來是中了催心掌掌勁的幹擾！\n" NOR;
}

