// baituo_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "baituo_poison"; }

string chinese_name() { return "白駝蛇毒"; }

string update_msg_others()
{
        return HIR "$N" HIR "一聲慘嚎，全身猶如萬射齊噬，痛苦不堪。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只覺全身奇痛無比，難以忍受。\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "焦枯的身子在地上撲騰了幾下，就再沒"
               "半點動靜了。\n" NOR;
}

string die_reason()
{
        return "被白駝蛇毒攻心而死";
}