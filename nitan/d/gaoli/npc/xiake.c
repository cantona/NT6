// 大唐雙龍傳

//俠客。

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("俠客", ({ "xia ke", "xia", "ke" }) );
        set("gender", "男性");
        set("age", 35);
        set("long","這是一個高麗的俠客，準備到中原去闖一番天下。\n");
        set("combat_exp", 300000+random(40000));
        set("attitude", "heroism");
        set("str", 30);
        set("max_qi", 1000);
        set("max_jing", 500);
        set("max_gin", 700);
        set("neili", 400);
        set("max_neili", 500);
        set("force_factor", 25);
        set_skill("blade", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);

        setup();

        carry_object("/d/gaoli/obj/gangdao")->wield();
        carry_object("//d/gaoli/obj/armor")->wear();
}


