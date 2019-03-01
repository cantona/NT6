// mafu.c 馬夫

inherit NPC;
#include <ansi.h>
int do_ride();

void create()
{
        set_name("馬夫", ({ "ma fu", "mafu", "ma"}));
        set("age", 32);
        set("gender", "男性");
        set("long","馴馬和租馬的小販，給他租金就可以雇到馬。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 50000);
        set("shen_type", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/armor", 30);
        set("chat_chance",2);
        setup();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
               remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_rideyz", "rideyz");
        add_action("do_rideht", "rideht");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say( "馬夫點頭哈腰地說道：這位客官，是想到這裡挑一匹好馬吧？\n");
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( query("money_id", ob) && ob->value() >= 100 )
        {
        message_vision("馬夫對$N說：好！這位"+RANK_D->query_respect(who) +
                "現在就出發馬? 那就上馬吧。\n", who);
                set_temp("marks/horserent", 1, this_player());
                       return 1;
        }
        else  
                message_vision("馬夫皺眉對$N說：您給的也太少了吧？\n", who);
        return 1;
}
#include "mafuyz.h"
#include "mafuht.h"
