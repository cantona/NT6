inherit NPC; 
int ask_me();
void create()
{
        set_name("蓮兒", ({ "lianer", "lian er"}) );
        set("gender", "女性" );
        set("age", 21);
        set("title", "精靈族女子");
        set("long",
        "蓮兒唱得一口好曲兒，長得楚楚動人，絕不遜色人類的女子。\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set("per",30);
        set_skill("unarmed",30);
        set_skill("dodge",80); 
      set("inquiry", ([
            "精靈之王" : (: ask_me :),
            "唱曲" : "“我是唱著玩的，讓你見笑了。”\n",
        ]) );

        setup();
   carry_object("/clone/cloth/cloth")->wear();
}

void do_sing(object ob)
{
   switch(random(2)) {
      case 0:
         message_vision("$N轉過來對$n微微一笑。\n\n",this_object(),ob);
         break;
      case 1:
         message_vision("$N回頭對$n輕輕一笑。\n\n",this_object(),ob);
         break;
   }
   set_temp("marks/song", random(2), this_object());
   set_temp("marks/songa", 0, this_object());
   call_out("singing",2, this_object());
}

int singing (object ob)
{
   int  song, songa; 
   object kid;
   remove_call_out("singing");
   song=query_temp("marks/song", ob);
   songa=query_temp("marks/songa", ob);
   switch(song) {
      case 0:
         switch(songa) {
            case 0:
               message_vision("$N清聲唱道：\n",ob);
               message_vision("        一年老一年，一日沒一日，一秋又一秋，一輩催一輩，\n",ob);
               set_temp("marks/songa", 1, ob);
   call_out("singing",2,ob);
               break;
            case 1:
               message_vision("        一聚一離別，一喜一悲。一榻一身臥，一生一夢裡。\n",ob);
               set_temp("marks/songa", 2, ob);
   call_out("singing",2,ob);
               break;
            case 2:
               message_vision("        尋一夥相識，他一會咱一會，都一般相知，吹一回，唱一回。\n\n",ob); 
               kid = present("kid", environment(ob));
               if(objectp(kid)) {
                  delete_temp("marks/sing", kid);
               }               break;
         }
         break;
      case 1: 
         switch(songa) {
            case 0:
   message_vision("$N輕敲竹板，婉聲唱道：\n",this_object());
   message_vision("  東邊路、西邊路、南邊路。五裡舖、七裡舖、十裡舖。\n",this_object());
               set_temp("marks/songa", 1, ob);
   call_out("singing",2,ob);
               break;
            case 1:
   message_vision("  行一步、盼一步、懶一步。霎時間天也暮、日也暮、雲也暮，\n",this_object());
               set_temp("marks/songa", 2, ob);
   call_out("singing",2,ob);
               break;
            case 2:
   message_vision("  斜陽滿地舖，回首生煙霧。兀的不山無數、水無數、情無數。\n",this_object());
               kid = present("kid", environment(ob));
               if(objectp(kid)) {
                  delete_temp("marks/sing", kid);
               } 
               break;
         }
         break;
   }
}

int ask_me()
{ 
       object me = this_player();
       remove_call_out("ask_for_help");

       command("say 你要見精靈之王？");
       command("shake");
       command("say 不可能的。她很少見外人。");
       call_out("ask_for_help",20); 

       return 1;
}

int ask_for_help()
{     
      object ob = this_object(); 
      object me = this_player();
      object where, obj;
      where=environment(me); 
      ob->move(where);command("tell"+query("id", me)+"不好了，三清湖有魚怪出現。求你幫幫我們！");
      command("say 我這裡有些東西，也許能派上用場。");
      obj=new("/quest/tulong/obj/string");
      obj->move(ob); 
      command("givestringto"+query("id", me));
      command("say 我家裡的東西你請隨意取用。請一定要制服魚怪！");
   ob->set("inquiry",([
            "魚怪" : "“聽說它已經成了精，會吃人的。”\n", 
            "精靈之王" : (: ask_me :),
            "唱曲" : "“我是唱著玩的，讓你見笑了。”\n",        ]));
      return 1;
}
