#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(HIR "腹蛇" NOR, ({ "fu she", "fu", "she" }));
        set("long", HIR "只見它全身血紅，頭呈三角，長蛇吞吐，嗤嗤做響。\n" NOR);

        set("age", 3);
        set("str", 35);
        set("dex", 50);
        set("max_qi", 1500);
        set("max_ging", 1500);
        set("combat_exp", 150000);

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("power", 22);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/parry", 100);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 80);
        set_temp("apply/armor", 100);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she" && arg!="fu she" && arg!="fu") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");
        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住蝮蛇的頭，右手輕撫其七寸，口中唸唸有詞，片刻間將蛇化為一根蛇杖。\n",
                me,);
                ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}