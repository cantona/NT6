inherit WORM;
#include <ansi.h>

void create()
{
        set_name(WHT "大頭蜈蚣" NOR, ({ "datou wugong", "datou", "wugong" }));
        set("long", WHT "這是一條全身細長，頭部碩大的蜈蚣。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 250);
        set("max_jing", 100);

        set("str", 40);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "尾巴" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 40,
                "perhit" : 20,
                "remain" : 30,
                "maximum": 30,
                "supply" : 2,
        ]));

        set("combat_exp", 1500 + random(1500));

        set_temp("apply/attack", 25);
        set_temp("apply/damage", 25);
        set_temp("apply/armor", 40);
        set_temp("apply/defence", 40);
        setup();
}

void die()
{
        message_vision(HIR "\n$N" HIR "倒在地上，死了。\n\n" NOR, this_object());
        destruct(this_object());
}