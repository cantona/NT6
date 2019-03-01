inherit NPC;

void create()
{
   set_name("蛇",({ "she"}) );
        set("race", "野獸" );
     set("long", "這是一條兇猛的蛇。\n");
         set("verbs",({"bite"}));
     set("limbs",({"頭","尾巴","七寸"}));
         set("attitude","aggressive");
         set("combat_exp",20000);
  setup();

}

void die()
{
        object ob,corpse;
        ob=this_object();
        message_vision("$N躺在地上晃了晃，死了過去。\n",ob);
    corpse=new(__DIR__"obj/shedan");
        corpse->move(environment(ob));
        destruct(ob);
        return;
}