// chenhu.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("陳滸", ({ "chen hu", "chen" }));
        set("title","金牛武館教習");
        set("long", "陳老爺子在武館也忙了幾十年了，仍勇於提攜後生。\n");
        set("gender", "男性");
        set("age", 65);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("cuff", 80);
        set_skill("staff", 80);
        set_skill("club", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/jinniu_paied", ob) == 1)return 0;
        return 1;
}