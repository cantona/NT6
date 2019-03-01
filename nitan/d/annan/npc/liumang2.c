inherit NPC;

void create()
{
   set_name("流氓頭子",({ "liu mang","liu","mang" }) );
        set("gender", "男性" );
        set("age", 22);
   set("long", "這是一個安南城內的流氓頭子。\n");
       
   set("combat_exp", 70000);
   set("str", 23);
   set("per", 18);
   set("attitude", "peaceful");
   set("chat_chance",50);
   set("chat_msg",({
           "流氓頭說道：這裡就是我們說了算！\n",
           "流氓頭罵道：都給我閃開，看什麼看！\n",
   }));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}
