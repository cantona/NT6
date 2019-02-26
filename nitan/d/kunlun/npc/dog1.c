// Npc: /d/kunlun/npc/dog1.c
// Last Modified by winder on Jun. 29 2001

inherit NPC;

void create()
{
        set_name("折衝將軍", ({ "dog"}) );
        set("race", "走獸");
        set("age", 4);
        set("long", "一隻昂首挺胸，吐着長舌頭的大惡狗。\n");
        set("attitude", "peaceful");
        
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
        if (living(this_object()) && interactive(ob = this_player()) &&
                random(ob->query_kar() + ob->query_per()) < 30)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob); 
        }        
}

void die()
{
        object ob;
        message_vision("$N慘嚎一聲，死了！\n", this_object());
        ob = new(__DIR__"obj/goupi");
        ob->move(environment(this_object()));
        destruct(this_object());
}
