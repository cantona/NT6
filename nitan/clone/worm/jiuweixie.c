inherit WORM;
#include <ansi.h>

void create()
{
        set_name(WHT "九尾蠍" NOR, ({ "jiuwei xie", "jiuwei", "xie" }));
        set("long", WHT "這是一隻丈來長，有九隻尾蟄的大蠍子。\n" NOR);
        set("race", "野獸");
        set("age", random(10));
        set("attitude", "peaceful");

        set("max_qi", 2000);
        set("max_jing", 1000);

        set("str", 30);
        set("con", 30);
        set("limbs", ({ "頭部", "身體", "尾巴" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 150,
                "perhit" : 20,
                "remain" : 60,
                "maximum": 60,
                "supply" : 1,
        ]));

        set("combat_exp", 300000 + random(300000));

        set_temp("apply/attack", 180 + random(180));
        set_temp("apply/damage", 180 + random(180));
        set_temp("apply/armor", 100 + random(100));
        set_temp("apply/defence", 100 + random(100));
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