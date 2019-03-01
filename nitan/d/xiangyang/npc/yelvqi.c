// yelvqi.c 耶律齊

#include <ansi.h>

inherit NPC;


void create()
{
        set_name("耶律齊", ({ "yelv qi", "yelv", "qi" }));
        set("title", "全真教第二代弟子 丐幫第二十一代幫主");
        set("gender", "男性");
        set("age", 25);
        set("per", 25);
        set("long",
        "郭靖和黃蓉的大女婿，郭芙的丈夫。\n",);

        set("combat_exp", 600000);
        set("shen_type", 1);

        set("max_neili", 2000);
        set("neili", 2000);
        set("jiali", 0);

        set_skill("force", 100);
        set_skill("sword", 100);
        set_skill("cuff", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("haotian-zhang" ,100);
        set_skill("quanzhen-jian" ,100);
        set_skill("kongming-quan",200);
        map_skill("cuff","kongming-quan");
        map_skill("strike","haotian-zhang");
        map_skill("sword","quanzhen-jian");
        map_skill("parry","quanzhen-jian");

        create_family("全真教", 2, "弟子");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 50);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}