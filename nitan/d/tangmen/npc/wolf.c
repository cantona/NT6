// wolf.c

inherit NPC;

void create()
{
        set_name("野狼", ({ "wolf","lang" }) );
        set("race", "野獸");
        set("age", 3);
        set("long", "一只瘦骨如柴的灰色餓狼。\n");
        set("attitude", "heroism");

        set("str",35);
        set("dex", 35);
        set("max_qi",600);
        set("qi",600);
        set("max_jingli",900);
        set("jingli",900);
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("chat_chance", 6);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "野狼張著血盆大嘴象你沖來。\n",
                "野狼對著你齜了齜牙。\n",
        }) );                

        set("combat_exp", 50000);

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 10);

        setup();
}

void init()
{
        object ob;
        ::init();

        if (living(this_object()) && interactive(ob = this_player()) && random(ob->query_kar() + ob->query_per()) < 30)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 2, ob); 
        }
}