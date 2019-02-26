inherit WORM;
#include <ansi.h>

void create()
{
        set_name(WHT "長腿蛛" NOR, ({ "changtui zhu", "changtui", "zhu" }));
        set("long", WHT "這是隻腿長寸許，全身毛茸茸的毒蜘蛛。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 200);
        set("max_jing", 100);

        set("str", 30);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "長腿", "肚子" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 30,
                "perhit" : 10,
                "remain" : 35,
                "maximum": 35,
                "supply" : 1,
        ]));

        set("combat_exp", 500 + random(500));

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
        set_temp("apply/armor", 15);
        set_temp("apply/defence", 20);
        setup();
}

void die()
{
        message_vision(HIR "\n$N" HIR "倒在地上，死了。\n\n" NOR, this_object());
        destruct(this_object());
}