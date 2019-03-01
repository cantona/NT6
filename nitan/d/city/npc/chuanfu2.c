// chuanfu.c 老船伕

#include <ansi.h>

inherit NPC;
void goto_matou1(object ob);

void create()
{
        set_name("老船伕", ({ "lao chuanfu","chuanfu" }));
        set("gender", "男性");
        set("age", 56);
        set("long",
                "這是一個老船伕。飽經風霜的臉上什麼也看不出來。\n",
        );

        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("str",800);

        set("max_neili", 100);
        set("neili", 100);
        set("jiali", 500);

        set_skill("force", 100);
        set_skill("unarmed", 300);
        set_skill("dodge", 100);
        set_skill("parry", 100);

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        int time;

        time = ob->value() / 100;
        time = 500 / time;
        if(time < 6)
                time = 6;

    if( query("money_id", ob) && ob->value() >= 2000 )
        {
        message_vision("老船伕對$N説：好！這位" + RANK_D->query_respect(who) + "請上船吧。\n" , who);
        who->move ("/d/city/duchuan");
                call_out("goto_matou1", time, who) ;
               return 1;
        }
    else  
                message_vision("老船伕皺眉對$N説：您給的也太少了吧？\n", who);
        return 0;
}
void goto_matou1(object ob)
{
   tell_object(ob, "渡船終於到岸了。你走下船來。\n" ) ;
   ob->move ("/d/shaolin/matou1") ;
}