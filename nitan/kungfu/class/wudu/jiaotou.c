#include <ansi.h>
#include "wudu.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("沙千里", ({ "sha qianli", "sha", "qianli" }));
        set("nickname", HIR "黑龍" NOR);
        set("long",@LONG
他就是五毒教的護法弟子沙千里，身材魁梧，方
面大耳。在教中轉管招募教眾，教授弟子們的入
門功夫。
LONG);
        set("title","五毒教護法弟子");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 40);
        set("combat_exp", 200000);
        set("score", 5000);

        set_skill("force", 80);
        set_skill("wudu-shengong", 80);
        set_skill("dodge", 80);
        set_skill("wudu-yanluobu", 80);
        set_skill("strike", 80);
        set_skill("tianchan-zhang", 80);
        set_skill("claw", 80);
        set_skill("wusheng-zhao", 80);
        set_skill("parry", 80);
        set_skill("literate", 50);
        set_skill("poison", 80);
        set_skill("wudu-qishu", 80 );
        set_skill("martial-cognize", 60);

        map_skill("force", "wudu-shengong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("claw", "wusheng-zhao");
        map_skill("parry", "wusheng-zhao");
        map_skill("poison", "wudu-qishu");

        prepare_skill("strike", "tianchan-zhang");
        prepare_skill("claw", "wusheng-zhao");

        set("coagents", ({
                ([ "startroom" : "/d/wudu/dating",
                   "id"        : "qi yunao" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "身形一晃，擋在$n" CYN
                                "跟前，厲聲説道：非本教弟子，不得進"
                                "入本教禁地。" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？快給我放下來！"
                                NOR,
        ]));

        create_family("五毒教", 13, "護法弟子");

        setup();

        carry_object("/d/wudu/npc/obj/ganggou")->wield();
        carry_object("/clone/cloth/cloth")->wear();

        add_money("silver",30);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say 我教弟子貴在隨心所欲，不收偽君子");
                return;
        }
        command("recruit "+query("id", ob));
        set("title", "五毒教教眾", ob);
        return;
}
