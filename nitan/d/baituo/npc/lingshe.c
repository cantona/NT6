// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// lingshe 西域靈蛇

#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name("靈蛇", ({ "ling she", "she", "snake" }) );
        set("race", "野獸");
        set("age", 4);
        set("long", "一條銀光閃閃的小蛇，產于西域，極為罕見。\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n沖$N嘶地一吐舌頭");
        set("msg_succ", "$n嘶嘶做響，蛇頭隨著$N的手動了起來");
        set("msg_trained","$n悄無聲息地遊到$N的腳下不動了");
        set("auto_follow",0);
        set("wildness", 90);

        set("str", 30);
        set("cor", 30);
        set("dex", 35);

        set("combat_exp", 100000);

        set_temp("apply/attack", 55);
        set_temp("apply/damage", 56);
        set_temp("apply/armor", 52);

        setup();
}

/*
void init()
{
        object ob;
        ::init();
        add_action("convert","bian");
        if (interactive(ob = this_player()) &&
            query("family/family_name", ob) != "歐陽世家" && 
                ! present("xiong huang", environment(ob))) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}

void unconcious()
{        
        write("靈蛇嗦地一下逃掉了。\n");
        destruct(this_object());
}
void die()
{
        object ob;
        ob = new("/d/baituo/npc/obj/shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        victim->apply_condition("bt_poison",10+query("snake_poison", me)+
                victim->query_condition("bt_poison"));
        if( query("bite_busy", me))victim->start_busy(2);
}
*/

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg != "ling she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");
        if (me->query_skill("training",1) < 70 + random(70)) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住靈蛇的頭，右手輕撫其七寸，口中念念有詞，片刻間將蛇化為一根蛇杖。\n",
                me,);
                ob = new("/d/baituo/obj/lingshezhang");
        ob->move(environment(this_object()));
        set("poison_applied", me->query_skill("poison",1)/2, ob);
        destruct(this_object());
        return 1;    
}