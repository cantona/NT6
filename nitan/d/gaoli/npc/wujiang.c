
inherit NPC;

void create()
{
   set_name("武將",({ "wu jiang","jiang","wu" }) );
   set("gender", "男性" );
   set("age", 32);
   set("long", "這是守衞高麗的武將，看起來十分威風。\n");
       
   set("combat_exp",800000);
   set("guard","高麗");
   set("attitude", "peaceful");
   
        set("str", 30);
        set("max_qi", 1000);
        set("max_jing", 500);
        set("max_mana", 700);
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
        carry_object("/d/gaoli/obj/armor")->wear();
   //set_this_skills("high");
   //set_all_skill(this_object(),180);
   
   setup();
  
}
