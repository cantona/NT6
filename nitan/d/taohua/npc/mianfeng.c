// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// wu.c 武眠風

inherit NPC;

string ask_me_2(string name);
void create()
{
        set_name("武眠風", ({ "wu mianfeng", "wu" }));
        set("long","
他是黃藥師的五弟子武眠風，他身材瘦小，沉默寡言，在江湖
上名聲不響，但卻極得黃藥師信任，顧而命他掌管桃花島藥房
重地。他在桃花弟子中尤精劍法。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 400000);

        set_skill("force", 120);
        set_skill("bibo-shengong", 120);
        set_skill("dodge", 120);
        set_skill("luoying-shenfa", 120);
        set_skill("strike", 120);
        set_skill("luoying-shenzhang", 120);
        set_skill("unarmed", 120);
        set_skill("luoying-shenjian", 120);
        set_skill("qimen-wuxing", 120);
        set_skill("xuanfeng-tui", 120);
        set_skill("hand", 120);
        set_skill("lanhua-shou", 120);
        set_skill("sword",120);
        set_skill("yuxiao-jianfa", 120);
        set_skill("literate", 80);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("strike", "luoying-shenzhang");
        map_skill("parry", "yuxiao-jianfa");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("sword","yuxiao-jianfa");

        prepare_skill("strike", "luoying-shenjian");

        create_family("桃花島", 2, "弟子");
        setup();
        set("inquiry", ([
                    "九花玉露丸" : (: ask_me_2, "yulu-wan" :)
        ]));

        set("drug_count", 3);
        set("yulu_count", 1);

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/taohua/obj/tiexiao")->wield();
}

string ask_me_2(string name)
{
        mapping fam; 
        object ob;
        
        if( !(fam=query("family", this_player())) || fam["family_name"] != "桃花島" )
                return RANK_D->query_respect(this_player()) + 
                "與本派素無來往，不知此話從何談起？";

        if( query("family/master_name", this_player()) != "黃藥師" )
                return "你功夫不夠，還是不要為妙。";                

        if (query("yulu_count") < 1)
                return "抱歉，你來得不是時候，已經發完了。";

        if (this_player()->query_condition("work") > 0)
                return "我不是才給過你藥嗎？怎麼又來要了，真是貪得無厭！";

        ob = new("/d/taohua/obj/"+name);
        ob->move(this_player(), 1);
        this_player()->apply_condition("work", 45);

        addn("yulu_count", -1);

        message_vision("武眠風給$N一粒"+query("name", ob)+"。\n",this_player());

        return "拿去吧。小心別弄丟了。";
}

int accept_kill(object me)
{
        if( query("family/family_name", me) == "桃花島"){
        command("say 你我本是同門，如何要加害于我！\n");
        set("th_killer", 1, me);
        kill_ob(me);
        return 1;
        }
        return 0;
}
void unconcious()
{
        object ob, me=this_object();

        if( objectp(ob=query_temp("last_damage_from", me) )
         && query("family/family_name", ob) == "桃花島" )
        set("th_killer", 1, ob);

        ::unconcious();
}