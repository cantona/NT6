// shi.c

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("史鏢頭", ({ "shi biaotou", "shi" }));
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"鏢頭"NOR);
        set("gender", "男性");
        set("age", 45);

        set("combat_exp", 7000);
        set("shen_type", 1);

        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 30);
        set_skill("dodge", 30);
        
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}