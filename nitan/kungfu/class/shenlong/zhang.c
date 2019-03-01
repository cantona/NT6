// This program is a part of NT MudLIB
// zhang.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("張淡月", ({ "zhang danyue", "zhang"}));
        set("title", HIY"神龍教"BLU"黑龍使"NOR);
        set("long", "這是一個黑衣大漢，身軀筆挺，容貌威嚴。\n" );
        set("gender", "男性");

        set("age", 44);
        set("str", 28);
        set("con", 26);
        set("int", 28);
        set("dex", 24);

        set("max_qi", 3200);
        set("qi", 3200);
        set("max_jing",1600);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 60);
        set("level", 16);
        set("combat_exp", 570000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 140);
        set_skill("huntian-qigong", 145);
        set_skill("dodge", 130);
        set_skill("feiyan-zoubi", 130);
        set_skill("unarmed", 130);
        set_skill("changquan", 130);
        set_skill("shedao-qigong", 140);
        set_skill("shenlong-xinfa", 140);
        set_skill("parry", 140);
        set_skill("staff", 140);
        set_skill("literate", 50);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("parry", "xianglong-zhang");

        create_family("神龍教", 0, "長老");

        set("coagents", ({
                ([ "startroom" : "/d/shenlong/dating",
                   "id"        : "hong antong" ]),
        }));

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "洪安通" : "教主脾氣不好,要討他歡心才好。\n",
                "教主"   : "教主脾氣不好,要討他歡心才好。\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！\n",
        ]));

        set("master_ob", 4);
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
        carry_object(__DIR__"obj/shenlongci")->wield();
        add_money("silver", 10);
}

void init()
{
        object ob;

        ::init();
        if (! objectp(ob)) return;
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
}

void greeting(object ob)
{
        object obj;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 100000);
                set("qi", 1000);
                set("jing", 1000);
        }
}

void attempt_apprentice(object ob)
{
        command("say 你走開！別煩我！");
        return;
}
