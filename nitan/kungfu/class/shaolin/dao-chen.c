// Npc: /kungfu/class/shaolin/dao-chen.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me(string name);

#include "dao.h"

void create()
{
        set_name("道塵禪師", ({
                "daochen chanshi",
                "daochen",
                "chanshi",
        }));
        set("long",
                "他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他手持兵\n"
                "刃，身穿一襲灰布鑲邊袈裟，似乎有一身武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 300);
        set("neili", 450);
        set("max_neili", 450);
        set("jiali", 40);
        set("combat_exp", 10000);
        set("score", 100);

        set_skill("force", 50);
        set_skill("hunyuan-yiqi", 50);
        set_skill("shaolin-xinfa", 50);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("strike", 50);
        set_skill("banruo-zhang", 50);
        set_skill("parry", 50);
        set_skill("damo-jian", 50);
        set_skill("buddhism", 50);
        set_skill("literate", 50);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("strike", "banruo-zhang");
        map_skill("parry", "damo-jian");

        prepare_skill("strike", "banruo-zhang");

        create_family("少林派", 39, "弟子");

        set("inquiry", ([
                "齊眉棍" : (: ask_me, "qimeigun" :),
                "戒刀" :   (: ask_me, "jiedao" :),
                "禪杖" :   (: ask_me, "chanzhang" :),
                "長劍" :   (: ask_me, "changjian" :),
                "皮鞭" :   (: ask_me, "changbian" :),
        ]));

        set("wuqi_count", 15);

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}

string ask_me(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "少林派" )
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if (  present(name, this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你現在身上不是有這樣武器嗎，怎麼又來要了？ 真是貪得無饜！";

        if (query("wuqi_count") < 1)
                return "抱歉，你來得不是時候，武器已經發完了。";

        ob = new("/d/shaolin/obj/" + name);
        ob->move(this_player());

        addn("wuqi_count", -1);

        message_vision("道塵給$N一件"+query("name", ob)+"。\n",this_player());

        return "拿去吧。不過要記住，武器只可防身練武，不可憑此殺害生靈。";
}
