// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("竹劍", ({ "zhu jian", "zhu", "jian"}));
        set("long", @LONG
梅劍、蘭劍、竹劍、菊劍四姐妹本是縹緲峰下
一家窮人的孩子。因無力撫養，被天山童姥看
中後收入門下。只見她容貌姣好，瓜子臉蛋又
眼如點漆，清秀絕俗。
LONG );
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("str", 23);
        set("int", 27);
        set("con", 25);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 40);
        set("level", 10);
        set("combat_exp", 500000);
        set("score", 3000);
        
        set_skill("force", 80);
        set_skill("xiaowuxiang", 80);
        set_skill("dodge", 80);
        set_skill("yueying-wubu", 80);
        set_skill("parry", 80);
        set_skill("strike", 100);
        set_skill("liuyang-zhang", 100);
        set_skill("sword", 80);
        set_skill("tianyu-qijian", 80);
        set_skill("literate", 120);
        set_skill("martial-cognize", 60);

        map_skill("force", "xiaowuxiang");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");

        prepare_skill("strike", "liuyang-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/lingjiu/dating",
                   "id"        : "xuzhu zi" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷笑道："
                                "什麼人？居然敢在我們靈鷲宮亂闖！"
                                NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：喂"
                                "！你這是把人搬到哪裡去呀？" NOR,
        ]));

        create_family("靈鷲宮", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ju" :),
                (: perform_action, "sword.shan" :),
                (: perform_action, "sword.huan" :),
        }));

        set("master_ob",2);
        setup();

        carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/lingjiu/obj/key");
        add_money("silver", 15);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "男性" )
        {
                command("consider");
                command("say 我看你還是去少林寺吧，我們主公天天都在懷念。");
                return;
        }

        if( query("gender", ob) != "女性" )
        {
                command("@@");
                command("say 這位公公，我看你還是趕緊回宮伺候皇上吧。");
                return;
        }

        command("xixi");
        command("say 既然這樣，那你就留在這兒下吧，以後我就是你師父了。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
}
