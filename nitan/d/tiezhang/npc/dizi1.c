// dizi1.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("巨木旗教眾", ({"dizi"}));
       set("long",
                "他是身材高大，兩臂粗壯，膀闊腰圓。他手持兵\n"
                "刃，身穿一綠色聖衣，似乎有一身武藝。\n"
        );

        set("gender", "男性");
        set("attitude", "peaceful");
        
        set("age", 35);
        set("shen_type", 0);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiaji", 50);
        set("combat_exp", 10000);
        set("score", 1);

        set_skill("force", 50);
        set_skill("blade",50);
        set_skill("cuff",50);
        
        set_skill("dodge", 50);
        
        set_skill("cuff", 50);
        set_skill("parry", 50);
        
       
        setup();
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object(__DIR__"obj/green-cloth")->wear();
}

void init()
{
        object me, ob;
        mapping fam;

        ::init();

        ob = this_player();
        me = this_object();
        
        if (interactive(ob) 
         && !query("no_fight", environment(ob) )
        && !present("shenhuo ling", ob) 
         && ((fam=query("family", ob)) && fam["family_name"] != "明教") )
        {
                if( !query_temp("warned", ob)){
                        command("say 你是誰？  怎麼闖到光明頂裏來了？！");
                        command("say 快給我速速離開，下次看到決不輕饒！");
                        set_temp("warned", 1, ob);
                }
                else if( query_temp("stay", ob)<10)addn_temp("stay", 1, ob);
                else {
                        command("say 大膽狂徒，竟敢闖到明教來撒野！！！\n");
                        remove_call_out("hiting_ob");
                             call_out("hiting_ob", 1, ob);
                }
        }       
}
int hiting_ob(object ob)
{
        object me;
        me=this_object();
        me->set_leader(ob);
        ob->kill_ob(me);
        me->fight_ob(ob);
        remove_call_out("moving_ob");
        call_out("moving_ob",1,ob);
}
int moving_ob(object ob)
{
        ob = this_player();
        if (!living(ob)){
        switch( random(3) ) {
        case 0:
                     command("say 哼，看你以後還敢不敢亂闖光明頂！！！");
        break;
        case 1:
                command("say 交給冷大人處理吧，關他一年半月的。");
        break;
        case 2:
                command("nod");
        break;
        }
        ob->move("/u/qingyun/mingjiao/jianyu");            
        }
        else {
        remove_call_out("hiting_ob");
        call_out("hiting_ob",1,ob);
        }
}