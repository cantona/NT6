// bihuochan.c 碧火蟾蜍

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name(HIG "碧火蟾蜍" NOR, ({ "bihuo chanchu" }) );
        set_weight(320);
        set("race", "野獸");
        set("age", 3);
        set("long", "一只癩蛤蟆，背上有一條條的綠色條紋。\n");
        set("attitude", "peaceful");
        set("str", 25);
        set("con", 25);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "蛙腿" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 80,
                "maximum": 50,
        ]));

        set("combat_exp", 8000);

        setup();
}