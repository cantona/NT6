// ren-yingying.c

inherit NPC;

void create()
{
        set_name("任盈盈", ({ "ren yingying", "yingying" }) );
        set("title","魔教聖姑");
        set("gender", "女性" );
        set("age", 19);
        set("str", 16);
        set("con", 30);
        set("int", 30);
        set("dex", 30);

        set("attitude", "friendly");

        set("qi",2500);
        set("max_qi",2500);
        set("jing",1200);
        set("max_jing",1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 30);

        set("long",     "任盈盈是魔教教主任我行的獨生女兒。\n");
        set("combat_exp", 250000);
        set("shen_tpye", 1);
        set_skill("unarmed", 90);
        set_skill("sword", 90);
        set_skill("force", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("literate", 100);

        set_skill("huashan-sword", 100);
        set_skill("huashan-neigong", 100);
        set_skill("huashan-quan", 100);
        set_skill("feiyan-huixiang", 100);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quan");
        map_skill("dodge", "feiyan-huixiang");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_fight(object me)
{
        command("say 小女子怎會是你的對手?");
        return 0;
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}
void greeting(object ob)
{
      say( "任盈盈微微歎了口氣：“不知道我的令狐大哥在何方?”\n");
      if ( ((int)ob->query_dex()>=25) && ((int)ob->query_int()>=25) )
      {
           tell_object(ob,"任盈盈説道：請你務必找到我令狐大哥.\n");
           set("marks/feng-qingyang", 1, ob);
      }
      tell_object(ob,"任盈盈所完這句話，飄然隱去.\n");
      call_out("goway",10);
}
void goway(){
      destruct(this_object());
}
