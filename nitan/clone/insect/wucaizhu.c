// wucaizhu.c 五彩蛛

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name(HIR "五" HIG "彩" HIW "蛛", ({ "wucai zhu" }) );
        set_weight(90);
        set("race", "野獸");
        set("age", 5);
        set("long", "一隻巨大的，五顏六色的大蜘蛛。\n");
        set("attitude", "peaceful");
        set("str", 18);
        set("con", 25);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 90,
                "maximum": 45,
        ]));

        set("combat_exp", 7000);

        setup();
}