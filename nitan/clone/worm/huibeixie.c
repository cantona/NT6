inherit WORM;
#include <ansi.h>

void create()
{
        set_name(WHT "灰背蠍" NOR, ({ "huibei xie", "huibei", "xie" }));
        set("long", WHT "這是一隻背部長滿了灰毛的毒蠍。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 200);
        set("max_jing", 100);

        set("str", 30);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "尾巴" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 25,
                "perhit" : 10,
                "remain" : 30,
                "maximum": 30,
                "supply" : 1,
        ]));

        set("combat_exp", 1000 + random(1000));

        set_temp("apply/attack", 25);
        set_temp("apply/damage", 25);
        set_temp("apply/armor", 20);
        set_temp("apply/defence", 20);
        setup();
}

void die()
{
        message_vision(HIR "\n$N" HIR "倒在地上，死了。\n\n" NOR, this_object());
        destruct(this_object());
}