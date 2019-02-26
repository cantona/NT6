// animal: snake.c
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("毒蛇", ({ "snake", "she" }) );
        set("race", "爬蛇");
        set("age", 4);
        set("long", "一隻有着三角形腦袋的蛇，尾巴沙沙做響。\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n衝$N嘶地一吐舌頭");
        set("msg_succ", "$n嘶嘶做響，蛇頭隨着$N的手動了起來");
        set("msg_trained","$n悄無聲息地游到$N的腳下不動了");
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
                query("family/family_name", ob) != "白駝山" && 
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}
void unconcious()
{        
        write("毒蛇嗦地一下逃掉了。\n");
        destruct(this_object());
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
        victim->apply_condition("snake_poison", 10 +
                victim->query_condition("snake_poison"));
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "白駝山" )
                return notify_fail("你不能化蛇為杖。\n");
        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住毒蛇的頭，右手輕撫其七寸，口中唸唸有詞，片刻間將蛇化為一根蛇杖。\n", me,);
        ob = new(__DIR__"obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}
