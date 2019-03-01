// mafu.c 馬夫

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("馬夫", ({ "ma fu", "mafu", "ma"}));
        set("age", 32);
        set("gender", "男性");
        set("long", "這是馬廄馴馬和小伙計，平時打理照料馬匹。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 50000);
        set("shen_type", 1);

        setup();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        say(CYN "馬夫點頭哈腰地說道：這位客官，您好，打算去哪兒啊？\n" NOR);
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "說道：你想去" NOR +
                               HIY "(goto)" NOR + CYN "哪兒？先告訴小的再付"
                               "錢也不遲。\n" NOR, this_object(), who);
                return 0;
        }

        return 0;
}
