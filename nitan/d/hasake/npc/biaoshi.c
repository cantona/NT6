#include <ansi.h>
inherit NPC;
void create()
{
       set_name("神祕鏢師", ({ "shenmi biaoshi", "biaoshi" }) );
       set("title", "中原鏢師");
       set("gender", "男性" );
       set("age", 45);
       set("str", 20);
       set("con", 20);
       set("int", 20);
       set("dex", 20);
       set("env/wimpy", 60);
       set("long", "他是個來自中原的鏢師，但他十年來從沒回去過，好像是在找什麼東西。\n" );
       set("combat_exp", 25000 + random(3000));
       set("shen", -300); 
       set("attitude", "heroism");
       set("chat_chance", 30);
       set("chat_msg", ({
            "神祕鏢師好像在自言自語：在哪呢？在哪呢？ \n",
           (: random_move :)
       }) );          
       set("max_qi", 400);
       set("max_jing", 400);
       set("neili", 500);
       set("max_neili", 500);
       set_skill("force", 30); 
       set_skill("unarmed", 30);
       set_skill("sword", 30);
       set_skill("dodge", 30);
       set_skill("parry", 30);       
       setup();       
       carry_object(WEAPON_DIR"changjian")->wield();
       carry_object(CLOTH_DIR"cloth")->wear();
       add_money("silver", 5);
}
