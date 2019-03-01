// tianshen.c 真龍天神
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "真龍天神" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIY "炎帝、黃帝、蚩尤同具真龍天神之像，擁有驚天動地\n"
                               "的能力，此能力僅傳于嫡系後人。獲得此技能者如為\n"
                               "「真命天子」則完成師門任務後獲取任務能力值獎勵\n"
                               "提高10%；如為「天煞孤星」則冥思獎勵提高10%。\n"
                               "同時，擁有該技能者可不再受限制，可同時擁有真命\n"
                               "天子及天煞孤星兩種天性。\n" NOR);


}