// hua.c

inherit NPC;

void create()
{
        set_name("華師傅", ({ "hua shifu", "hua" }));
        set("gender", "男性");
        set("age", 65);
        set("long", 
"他是鏢局中的廚子，烹飪功夫著實不差，幾位冬瓜盅、佛跳牆、糟魚、肉
皮餛飩，馳譽福州，是林震南結交達官富商的本錢之一。\n");
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