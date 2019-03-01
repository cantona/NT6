// /d/shenlong/obj/qingshe.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("竹葉青蛇", ({ "qing she", "she" }) );
        set("race", "爬蛇");
        set("age", 2);
        set("long", "一隻讓人看了起雞皮疙瘩的竹葉青蛇。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("cor", 20);
        set("combat_exp", 3000+random(300));

        set_temp("apply/attack", 18);
        set_temp("apply/damage", 15);
        set_temp("apply/armor", 12);
        set_temp("apply/defence",16);

        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(this_player()))
        {
                if (!(ob = present("xionghuang", this_player())))
                {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, this_player());
                }
        }
}

void die()
{
        object ob;
        message_vision("$N倒在地上，死了！\n", this_object());
        ob = new("/d/baituo/obj/qingdan");
        ob->move(environment(this_object()));
        destruct(this_object());
}

int hit_ob(object me, object ob, int damage)
{
        if( query("combat_exp", ob)>10000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && 
                (int)ob->query_condition("snake_poison") < 10 )
        {
                ob->apply_condition("snake_poison", 20);
                tell_object(ob, HIG "你覺得被咬中的地方一陣麻木！\n" NOR );
        }
}
