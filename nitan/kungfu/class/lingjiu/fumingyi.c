// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("符敏儀", ({ "fu mingyi", "fu", "mingyi"}));
        set("long", @LONG
符敏儀乃是縹緲峯靈鷲宮中九天九部中陽天部
的副首領。只見她已經四十開外，卻仍是風華
不減，頗有韻味。
LONG);
        set("title", "縹緲縫靈鷲宮");
        set("nickname", HIM "陽天部首領" NOR);
        set("gender", "女性");
        set("age", 37);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 2800);
        set("max_qi", 2800);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 80);
        set("level", 10);
        set("combat_exp", 1000000);
        set("score", 3000);
        
        set_skill("force", 140);
        set_skill("xiaowuxiang", 140);
        set_skill("dodge", 160);
        set_skill("yueying-wubu", 160);
        set_skill("parry", 140);
        set_skill("strike", 120);
        set_skill("liuyang-zhang", 120);
        set_skill("sword", 140);
        set_skill("tianyu-qijian", 140);
        set_skill("literate", 180);
        set_skill("martial-cognize", 120);

        map_skill("force", "xiaowuxiang");
        map_skill("strike","liuyang-zhang");
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

        if ((int)ob->query_skill("xiaowuxiang", 1) < 30) 
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
