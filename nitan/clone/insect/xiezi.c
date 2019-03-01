// xiezi.c 蠍子

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("蠍子", ({ "xie zi" }) );
        set_weight(180);
        set("race", "野獸");
        set("age", 2);
        set("long", "一只張牙舞爪的蠍子。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 30,
                "maximum": 25,
        ]));

        set("combat_exp", 100);

        setup();
}