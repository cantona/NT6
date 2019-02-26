// jinlin.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("金臨", ({ "jinlin", "jin" }) );
        set("gender", "男性" );
        set("age", 18);
        set("long", "這是一位垂髫童子，是魯班手下五行童子之一。\n");
        set("title", HIC "南方丙丁" NOR CYN "◎" HIR "火" NOR);
        set("nickname", HIY "五行童子" NOR);
        set("attitude", "friendly");
        setup();
}

int accept_object(object who, object ob)
{
        command("say 邊兒去！東西不要給我。");
        return 0;
}

int accept_ask()
{
        message_vision("$N半答不理的説：有啥事問我師傅去，別煩我。\n",
                       this_object());
        return 1;
}