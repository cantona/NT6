// xuexue.c 雪蠍子

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name(WHT "雪蠍子" NOR, ({ "xue xie" }) );
        set_weight(180);
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻晶瑩剔透的蠍子。\n");
        set("attitude", "peaceful");
        set("str", 25);
        set("con", 22);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "腳", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 80,
                "maximum": 45,
        ]));

        set("combat_exp", 10000);

        setup();
}