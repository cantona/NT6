//qingshe.c 冰蠶

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("冰蠶", ({ "bing can", "can" }) );
        set_weight(100);
        set("race", "野獸");
        set("age", 2);
        set("long", "一只渾身上下透體通明的蠶。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "頭部", "身體", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 400,
                "maximum": 400,
        ]));

        set("combat_exp", 100);

        setup();
}