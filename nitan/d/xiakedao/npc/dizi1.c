// dizi1.c 弟子
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("俠客島弟子", ({ "di zi", "di", "zi" }));
        set("long", "這是三十多歲的壯漢，膀大腰圓，是島主從中原招募來的。\n");

        set("gender", "男性");
        set("age", 30);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("qi", 500);
        set("max_qi", 500);
        set("jing", 200);
        set("max_jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 30);

        set("combat_exp", 30000);
        set("score", 10);
        set_skill("force", 70);
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("hand", 70);
        set_skill("staff", 50);

        create_family("俠客島", 2, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        ob = this_player();
        if (interactive(ob) && !ob->is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        object room;
        room = find_object("/d/xiakedao/dongmen");

        if( !ob || environment(ob) != environment()
                || environment() != room)
                return;
        switch( random(2) )
        {
                case 0:
                        say( "俠客島弟子說道：這位" + RANK_D->query_respect(ob)
                                 + "，快請到迎賓館中歇歇腳吧。\n");
                        break;
                case 1:
                        say( "俠客島弟子恭手說道：這位" + RANK_D->query_respect(ob)
                                 + "，島主正在等你呢。\n");
                        break;
        }
}
