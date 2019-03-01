// 大唐雙龍傳
//shi1.c 小兵
 
inherit NPC;

void create()
{
        set_name("武士", ({ "wu shi", "wushi", "shi" }));
        set("age", 18+random(10));
        set("gender", "男性");
        set("long","這是一名供奉于高麗宮廷的武士，穿著一身武士裝，威風凜凜\n");
        set("attitude", "peaceful");
   set("str", 20);
        set("combat_exp", 350000);
   set("max_qi", 1400);
   set("max_mana", 1200);
   set("max_jing", 1400);
   set("max_neili", 1200);
   set("neili", 1200);
   set("force_factor", 100);
        set_skill("unarmed", 140);
        set_skill("dodge", 140);
        set_skill("parry", 140);
        set_skill("blade", 140);
        set_skill("force", 140);

        setup();
        carry_object("/d/gaoli/obj/gangdao")->wield();
        carry_object("/d/gaoli/obj/armor")->wear();
}
