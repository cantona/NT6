inherit WORM;
#include <ansi.h>

void create()
{
        set_name(CYN "鐵骨蠍" NOR, ({ "tiegu xie", "tiegu", "xie" }));
        set("long", CYN "這是一條全身閃著磷光的毒蠍子。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 500);
        set("max_jing", 300);

        set("str", 40);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "尾巴" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 70,
                "perhit" : 10,
                "remain" : 45,
                "maximum": 45,
                "supply" : 1,
        ]));

        set("combat_exp", 25000 + random(25000));

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 200);
        set_temp("apply/defence", 100);
        setup();
}

void die()
{
        message_vision(HIR "\n$N" HIR "倒在地上，死了。\n\n" NOR, this_object());
        destruct(this_object());
}