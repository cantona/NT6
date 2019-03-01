// liuhongying.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("劉虹瑛", ({ "liu hongying", "liu" }));
        set("title","金牛武館教習");
        set("long", "劉教頭是武館的新來教習，你可別小看她哦。\n");
        set("gender", "女性");
        set("age", 32);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("strike", 80);
        set_skill("sword", 80);
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