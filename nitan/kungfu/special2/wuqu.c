// zhuha.c 朱蛤奇緣
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "武曲轉世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在轉世時巧遇武曲星投胎轉世，藉助昊\n"
						   "天塔神力，你獲取武曲星附體轉生，擁有\n"
						   "常人沒有的武學領悟能力。轉生後擁有該\n"
						   "技能可以提高所有武學研究速度百分之十，\n"
						   "並且打坐、吐吶速度提高百份之五十，汲\n"
						   "取實戰體會速度提高百分之五十。\n");

}