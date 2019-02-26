// huoxie.c 火蠍子

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("火蠍子", ({ "huo xie zi", "huo xie" }) );
        set_weight(220);
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻火紅色的大蠍子。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 60,
                "maximum": 25,
        ]));

        set("combat_exp", 100);

        setup();
}