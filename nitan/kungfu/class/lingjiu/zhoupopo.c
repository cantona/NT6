// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("周婆婆", ({ "zhou popo", "zhou", "popo" }));
        set("long", @LONG
餘婆婆是縹緲峯靈鷲宮中九天九部中鸞天部的
首領。她如今年過半百，跟隨童姥多年，出生
入死，飽經風霜。
LONG);
        set("title", "縹緲縫靈鷲宮");
        set("nickname", HIW "鸞天部首領" NOR);
        set("gender", "女性");
        set("age", 60);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3200);
        set("max_qi", 3200);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 3600);
        set("max_neili", 3600);
        set("jiali", 100);
        set("level", 15);
        set("combat_exp", 1000000);
        set("score", 3000);
        
        set_skill("force", 160);
        set_skill("xiaowuxiang", 160);
        set_skill("dodge", 140);
        set_skill("yueying-wubu", 140);
        set_skill("parry", 140);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("sword", 140);
        set_skill("tianyu-qijian", 140);
        set_skill("literate", 180);
        set_skill("martial-cognize", 120);

        map_skill("force", "xiaowuxiang");
        map_skill("strike", "liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");

        prepare_skill("strike", "liuyang-zhang");

        create_family("靈鷲宮", 2, "首領");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ju" :),
                (: perform_action, "sword.shan" :),
                (: perform_action, "sword.huan" :),
        }));

        set("master_ob",3);
        setup();

        carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 15);
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
         && ((fam=query("family", ob)) && fam["family_name"] != "靈鷲宮") )
        {
                if( !query_temp("warned", ob) )
                {
                        command("say 尊主有令：外人不得進入靈鷲宮，速速離開！");
                        set_temp("warned", 1, ob);
                } else 
                if( query_temp("stay", ob)<5 )
                        addn_temp("stay", 1, ob);
                else 
                {
                        command("say 大膽狂徒，竟敢擅闖靈鷲宮！！！\n");
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
                }
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "男性" )
        {
                command("hmm");
                command("say 走開，靈鷲宮素來不收男徒。");
                return;
        }

        if( query("gender", ob) != "女性" )
        {
                command("sneer");
                command("say 靈鷲宮又不是皇宮，你一個太監跑來做甚？");
                return;
        }

        if ((int)ob->query_skill("xiaowuxiang", 1) < 40) 
        {
                command("say 你把本門的心法煉好了再來找我。");
                return;
        }

        command("nod2");
        command("say 那你以後就跟着我吧。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
}
