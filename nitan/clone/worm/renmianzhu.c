inherit WORM;
#include <ansi.h>

void create()
{
        set_name(HIY "人面蛛" NOR, ({ "renmian zhu", "renmian", "zhu" }));
        set("long", HIY "一只臉盆大小的毒蜘蛛，面部便如嬰臉一般。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 2000);
        set("max_jing", 1000);

        set("str", 30);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "長腿" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 160,
                "perhit" : 40,
                "remain" : 45,
                "maximum": 45,
                "supply" : 10,
        ]));

        set("combat_exp", 250000 + random(250000));

        set_temp("apply/attack", 120 + random(120));
        set_temp("apply/damage", 120 + random(120));
        set_temp("apply/armor", 150 + random(150));
        set_temp("apply/defence", 150 + random(150));
        setup();
}

void die()
{
        object ob;
        message_vision(HIR "\n$N" HIR "倒在地上，死了。\n\n" NOR, this_object());
        ob = new(__DIR__"obj/dunang");
        ob->move(environment(this_object()));
        destruct(this_object());
}