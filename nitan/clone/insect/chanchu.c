// chanchu.c 蟾蜍

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("蟾蜍", ({ "chan chu" }) );
        set_weight(350);
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻長得極為噁心的癩蛤蟆。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "蛙腿" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 20,
                "maximum": 30,
        ]));

        set("combat_exp", 100);

        setup();
}