// di.c

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("狄鏢頭", ({ "di biaotou", "di" }));
        set("gender", "男性");
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"鏢頭"NOR);
        set("age", 45);

        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("unarmed", 30);
        set_skill("blade", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/damage", 30);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}