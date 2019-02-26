// heiguafu.c 黑寡婦

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("黑寡婦", ({ "hei guafu" }) );
        set_weight(80);
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻長得巨大的醜陋無比的大蜘蛛。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 80,
                "maximum": 30,
        ]));

        set("combat_exp", 100);

        setup();
}