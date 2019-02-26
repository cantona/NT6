inherit NPC;
void create()
{
  set_name("高麗勇士",({ "gaoli yongshi","yongshi"}) );
        set("gender", "男性" );
        set("age", 35);
   set("long", "這是高麗的勇士，在高麗少有敵手。\n");
   set("combat_exp",1500000+random(3000));
   set_skill("dodge",680);
   set_skill("parry",680);
   set_skill("unarmed",680);
   set("attitude", "peaceful");
   set("chat_chance",20);
   set("chat_msg",({
    "高麗勇士一笑：誰敢和我挑戰？真是活得不耐煩了！\n",
    "高麗勇士朝你哼了一聲：小角色，以後別讓我見到你！\n",
    "高麗勇士把頭一昂，冷冷地看了你一眼。\n",
    "高麗勇士一曬：據説誰殺了我會得到什麼稱號，我看這樣的人還沒出生呢！\n",
    }));
  setup();
  
}

void die()
{
   object ob;
   
   ob=query_temp("last_damage_from");
   
   if(!ob) return ::die();
   if(!userp(ob)) return ::die();
   
   if(random(100)>95){
     CHANNEL_D->do_channel(this_object(),"rumor",ob->name()+"殺死高麗勇士，獲得了"+
      "「高麗王者」的稱號！\n");
     ob->set_temp("rank/class","高麗王者");
   }
   
   return ::die();
   
}
