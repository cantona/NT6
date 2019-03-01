// duzhu.c 毒蜘蛛

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("毒蜘蛛", ({ "du zhu" }) );
        set_weight(40);
        set("race", "野獸");
        set("age", 2);
        set("long", "一只背上有斑斑點點的的花蜘蛛，看來有劇毒。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 40,
                "maximum": 20,
        ]));

        set("combat_exp", 100);

        setup();
}