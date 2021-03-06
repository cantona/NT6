// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("褚萬里", ({ "chu wanli", "chu" }));
        set("title", "大理國護衞" );
        set("long", "他是大理國四大護衞之一，英氣逼人。\n");
        set("gender", "男性");
        set("age", 40);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1800);
        set("max_jing", 1000);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 50);
        set("level", 10);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("kurong-changong", 120);
        set_skill("dodge", 120);
        set_skill("tiannan-bu", 120);
        set_skill("cuff", 120);
        set_skill("jinyu-quan", 120);
        set_skill("strike", 120);
        set_skill("wuluo-zhang", 120);
        set_skill("whip", 140);
        set_skill("feifeng-bian", 140);
        set_skill("parry", 120);
        set_skill("literate", 80);
        set_skill("martial-cognize", 140);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("whip", "feifeng-bian");
        map_skill("parry", "feifeng-bian");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/dali/neitang",
                   "id"        : "duan zhengchun", ]),
        }));

        set("guarder", ([
                "refuse_home" : CYN "$N" CYN "攔住$n" CYN "道：對不"
                                "起！王爺有令，出了段家就莫回來。\n" NOR,
                "refuse_other": CYN "$N" CYN "一把攔住$n" CYN "，喝"
                                "道：閒雜人等，不能入內。\n" NOR,
                "refuse_carry": CYN "$N" CYN "陪着笑臉對$n" CYN "道"
                                "：可否將…你背的人放下再進王府？\n" NOR,
        ]));

        create_family("段氏皇族", 15, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "whip.xi" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object(__DIR__"obj/diaogan")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("shake");
        command("say 世子殿下何需如此，只要有事吩咐在下一聲便是。");
        return;
}
