// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("程青霜", ({ "cheng qingshuang", "cheng"}));
        set("long", @LONG
程青霜乃是縹緲峰靈鷲宮中九天九部中鈞天部
的副首領。只見她三十開外，長得頗有姿色。
LONG);
        set("title", "縹緲縫靈鷲宮");
        set("nickname", HIY "鈞天部副首領" NOR);
        set("gender", "女性");
        set("age", 37);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 2400);
        set("max_qi", 2400);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 80);
        set("level", 10);
        set("combat_exp", 800000);
        set("score", 3000);
        
        set_skill("force", 120);
        set_skill("xiaowuxiang", 120);
        set_skill("dodge", 120);
        set_skill("yueying-wubu", 120);
        set_skill("parry", 120);
        set_skill("strike", 120);
        set_skill("liuyang-zhang", 120);
        set_skill("sword", 140);
        set_skill("tianyu-qijian", 140);
        set_skill("literate", 150);
        set_skill("martial-cognize", 100);

        map_skill("force", "xiaowuxiang");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");

        prepare_skill("strike", "liuyang-zhang");

        create_family("靈鷲宮", 3, "副首領");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ju" :),
                (: perform_action, "sword.shan" :),
                (: perform_action, "sword.huan" :),
        }));

        set("master_ob",3);
        set("master_ob",2);
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

        if ((int)ob->query_skill("xiaowuxiang", 1) < 25) 
        {
                command("say 你把本門的心法煉好了再來找我。");
                return;
        }

        command("nod2");
        command("say 那你以後就跟著我吧。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
}
