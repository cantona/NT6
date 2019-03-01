// taxue.c 踏雪無痕
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "踏雪無痕" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIW "由于掌握了萬物變換真諦，能夠充分激發體內的潛力，\n"
                               "使自身在忙亂的時候可以有一定幾率降低忙亂時間，\n"
                               "綜合效果不如左右互搏及腰帶鑲嵌效果，但是可以和\n"
                               "左右互搏及腰帶鑲嵌效果兼容。\n"
                               "同時，在研究輕功類技能的時候速度提升50%。\n" NOR);

}