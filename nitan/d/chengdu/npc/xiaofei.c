// xiaofei.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("蕭飛", ({ "xiao fei", "xiao" }));
        set("title","金牛武館教習");
        set("long", "蕭教頭是武館的新來教習，但他的弟子也有在江湖出頭的了。\n");
        set("gender", "男性");
        set("age", 35);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("finger", 80);
        set_skill("throwing", 80);
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