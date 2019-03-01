//jinshe.c
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("金環蛇", ({ "jin she", "she" }) );
        set("race", "爬蛇");
        set("age", 2);
        set("long", "一隻讓人看了起毛骨悚然的金環蛇。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("cor", 20);
        set("combat_exp", 1500+random(200));

        set_temp("apply/attack", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 18);
        set_temp("apply/defence",15);
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
        ob = new("/d/baituo/obj/jindan");
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
