// wubushe.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("五步蛇", ({ "wubushe" }) );
        set("long", "五步蛇是福建地方毒蛇，相傳中毒行路五步即行倒斃。\n");
        set("race", "爬蛇");
        set("age", 3);
        set("attitude", "peaceful");

        set("max_ging", 80);
        set("max_qi", 80);

        set("str", 10);
        set("cor", 50);

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if (interactive(me = this_player()))
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
        if( query("combat_exp", ob)>10000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && 
                (int)ob->query_condition("snake_poison") < 10 )
        {
                ob->apply_condition("snake_poison", 40);
                tell_object(ob, HIG "你覺得被咬中的地方一陣麻木！\n" NOR );
        }
}