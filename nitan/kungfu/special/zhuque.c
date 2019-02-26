// zhuque.c 朱雀重生
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "朱雀重生" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIR "獲得烈火鳳凰般的體魄， 死亡後有40%機率不損失技\n"
                           "能並且在暈倒的時候有50% 機率獲得體內潛力的瞬間爆發，\n"
                           "氣血及精力可瞬間自動恢復60%，躲避暈倒，特別在戰鬥中\n"
                           "可降低因為暈倒而死亡的可能。（如打通生死玄關後死亡不\n"
                           "丟失技能的機率將根據生死玄關的效果累積）\n" NOR);
}