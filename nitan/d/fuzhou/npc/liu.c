// liu.c

#include <ansi.h>;
inherit NPC;
int ask_jiaobiao();
void create()
{
        set_name("劉鏢頭", ({ "liu biaotou", "liu" }));
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"大鏢頭"NOR);
        set("gender", "男性");
        set("age", 45);

        set("combat_exp", 50000);
        set("shen_type", 1);
        set("no_get", 1);
        set_skill("unarmed", 30);
        set_skill("blade", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        set("inquiry", ([
                "交鏢"   : (: ask_jiaobiao :),
                "finish" : (: ask_jiaobiao :),
        ]));
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/damage", 30);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
void init()
{        
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( query_temp("fuwei_ready", ob) )
        {
                say(query("name", this_object())+"笑咪咪地對"+query("name", ob)+"說道：這位"+RANK_D->query_respect(ob)+"，是來交鏢的吧。你的鏢隊和鏢車都齊全吧？\n");
        }
}

#include "biaotou.h"