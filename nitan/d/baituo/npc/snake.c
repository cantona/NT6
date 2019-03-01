// Code of ShenZhou
// animal: snake.c
// Jay 3/18/96
#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name("毒蛇", ({ "snake", "she" }) );
        set("age", 4);
        set("long", "一只有著三角形腦袋的蛇，尾巴沙沙做響。\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n沖$N嘶地一吐舌頭");
        set("msg_succ", "$n嘶嘶做響，蛇頭隨著$N的手動了起來");
        set("msg_trained","$n悄無聲息地遊到$N的腳下不動了");
        set("auto_follow",0);
        set("wildness", 9);

        set("str", 26);
        set("cor", 30);

        set("combat_exp", 1000);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void init()
{
        object ob;
        ::init();
        add_action("convert","bian");
        if (interactive(ob = this_player()) &&
            query("family/family_name", ob) != "歐陽世家" && 
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}
void die()
{
        object ob;
        ob = new(__DIR__"obj/shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int poison;
       poison=query("snake_poison", me);

        if( poison>0 && !query("snake_poison", victim) )
             victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id":query("id", me),
                                 "duration" :  poison/20 ]));
       return HIR "只聽$n痛呼了一聲，給毒蛇狠狠的咬了一口！\n" NOR;
        if( query("bite_busy", me))victim->start_busy(2);
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");
        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住蛇頭，右手輕撫其七寸，口中念念有詞，片刻間將蛇化為一根蛇杖。\n",
                me,);
                ob = new("/d/baituo/npc/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}
