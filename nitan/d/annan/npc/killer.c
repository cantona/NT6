inherit NPC;

void create()
{
   set_name("安南盜賊",({ "dao zei","dao","zei" }) );
        set("gender", "男性" );
        set("age", 42);
   set("long", "這是一個流竄于江湖的盜賊，近日被長安的捕頭通緝。\n");
       
   set("combat_exp",100000);
   set("str", 28);
   set("per", 20);
   set("attitude", "friendly");
   set_skill("dodge",80);
   set_skill("parry",80);
   set_skill("unarmed",80);
   set_skill("force",80);
   set("max_force",300);
   set("force",300);
   set("jiali",20);
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

void die()
{
        object ob;object here;
        ob=query_temp("last_damage_from", this_object());
        if( query_temp("butou_job/1", ob) )
                set_temp("butou_job_ok", 1, ob);
        return ::die();
}