//fushe.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("蝮蛇", ({ "fushe", "she", "fu" }) );
        set("race", "野獸");
        set("age", random(10));
        set("long", "只見它全身血紅，頭呈三角，長蛇吞吐，嗤嗤做響。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("cor", 20);
        set("limbs", ({ "頭部", "身體", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 30000+random(50000));

        set_temp("apply/attack", 20+random(10));
        set_temp("apply/damage", 10+random(10));
        set_temp("apply/armor", 15+random(10));
        set_temp("apply/defence",20+random(10));
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if ( interactive(me = this_player()) && living(this_object()) )
        {
                if (!(ob = present("xionghuang", this_player())))          
                       {
                               remove_call_out("kill_ob");
                               call_out("kill_ob", 1, me);
                        }
        }
}

int hit_ob(object me, object ob, int damage)
{
        if( query("combat_exp", ob)>100000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && ob->query_condition("snake_poison")<20 )
        {
                ob->apply_condition("snake_poison", 40);
                tell_object(ob, HIG "你覺得被咬中的地方一陣麻木！\n" NOR );
        }
}

void die()
{
        object ob;
        message_vision("$N倒在地上，死了！\n", this_object());
//        ob = new("/d/shenlong/obj/shedan");
//        ob->move(environment(this_object()));
//        ob = new("/d/baituo/obj/shepi");
//        ob->move(environment(this_object()));
        destruct(this_object());
}