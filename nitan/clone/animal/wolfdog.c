// wolfdog.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("大狼狗", ({ "wolf dog", "dog" }) );
        set("race", "走獸");
        set("age", 4);
        set("long", "一隻昂首挺胸，吐着長舌頭的大狼狗。像是財主家裏養的寵物。\n");
        set("attitude", "peaceful");
        
        set("str", 26);
        set("cor", 30);

        set("combat_exp", 1000);

        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "大狼狗大聲吠叫：汪！汪！汪！汪！汪！汪！\n",
                "大狼狗突然跳了起來，口中亂咬，卻不知道是在咬誰。\n"
        }) );
                
        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                !query("no_fight", environment()) && 
                random(ob->query_kar() + ob->query_per()) < 30)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob); 
        }
}

void die()
{
        object ob;
        ob = new(__DIR__"obj/goupi");
        ob->move(environment(this_object()));
        destruct(this_object());
}