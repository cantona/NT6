// mazei.c

inherit NPC;

void create()
{
        set_name("馬賊", ({ "ma zei", "zei" }));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("per", 16);
        set("long", "一個彪悍的馬賊。\n");
        set("combat_exp", 50000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/d/city/npc/obj/tiejia")->wear();
}

void init()
{
        object ob;
        ::init();

        if( interactive(ob=this_player()) && query_temp("mazei", ob) )
        {
                say( "馬賊對着你大吼：你竟敢不交！老子宰了你！\n");
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
        if( interactive(ob) && !is_fighting() && !query_temp("mazei", ob) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say( "馬賊橫刀當道，一聲大喊：此山是我開，此樹是我栽，若要
從此過，留下買路財 !\n");
        say( "馬賊説道：識相點兒，寶貝兒留下來就讓你小子走！\n");
        set_temp("mazei", 1, ob);
}

int accept_object(object who, object ob)
{

        if( query("money_id", ob) && ob->value() >= 5000 )
        {
             say( "馬賊大喊一聲：既然交了錢，就請馬前過。\n");
             delete_temp("mazei", ob);
                return 1;
        }
       say( "馬賊大怒：就這麼點錢？\n");
       return 0;
}

