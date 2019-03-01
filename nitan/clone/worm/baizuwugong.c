inherit WORM;
#include <ansi.h>

void create()
{
        set_name(HIB "百足蜈蚣" NOR, ({ "baizu wugong", "baizu", "wugong" }));
        set("long", WHT "這是一條一尺多長的蜈蚣，長有百足。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 250);
        set("max_jing", 100);

        set("str", 30);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "尾巴" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 20,
                "perhit" : 10,
                "remain" : 30,
                "maximum": 30,
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