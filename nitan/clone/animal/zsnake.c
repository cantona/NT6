// animal: snake.c
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("竹葉青", ({ "zhuye qing", "snake" }) );
        set("race", "爬蛇");
        set("age", 4);
        set("long", "一只身體碧綠的蛇，顯得特別細小。\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n沖$N嘶地一吐舌頭");
        set("msg_succ", "$n嘶嘶做響，蛇頭隨著$N的手動了起來");
        set("msg_trained","$n悄無聲息地遊到$N的腳下不動了");
        set("auto_follow",0);
        set("wildness", 11);

        set("str", 26);
        set("cor", 30);

        set("combat_exp", 3000);

        set_temp("apply/attack", 25);
        set_temp("apply/damage", 9);
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
void die()
{
        object ob;
        ob = new(NOSTRUM_DIR"shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        victim->apply_condition("snake_poison", 20 +
                victim->query_condition("snake_poison"));
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="zhuye qing") return 0;
        if( query("family/family_name", me) != "白駝山" )
                return notify_fail("你不能化蛇為杖。\n");
        return notify_fail("竹葉青過于細小，不能化為杖。\n");
}
