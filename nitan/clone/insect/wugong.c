// wugong.c 蜈蚣

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("蜈蚣", ({ "wu gong" }) );
        set_weight(100);
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻蜈蚣。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 35,
                "maximum": 20,
        ]));

        set("combat_exp", 100);

        setup();
}