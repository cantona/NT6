inherit NPC;
void create()
{
        set_name("弟弟", ({ "kid"}) );
        set("gender", "男性" );
        set("age", 5);
        set("title", "精靈族小孩");
        set("long",
                "他光着身子，眉清目秀，可愛之極。\n");
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("per",15);
        set_skill("unarmed",50);
        set_skill("dodge",50);

        setup();
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        object  lianer;

        if( !ob || environment(ob) != environment() ) return;
        lianer = present("lian er", environment(ob));
        if(!objectp(lianer)){
message_vision("$N説：“蓮兒姐唱的歌最好聽了！”\n",this_object(),ob);
           return;
        }
        if(query_temp("marks/sing") == 1) {
           return;
        }
        switch( random(2) ) {
                case 0:
message_vision("$N搖着蓮兒的手，説：“蓮兒姐姐，唱個小調給我聽吧。”\n",this_object(),ob);
                        break;
                case 1:
message_vision("$N纏着蓮兒，説：“姐姐，我要聽小曲兒！”\n",this_object(),ob);
                        break;
        }
        set_temp("marks/sing", 1, this_object());
        lianer->do_sing(ob);
}

int accept_object(object who, object ob)
{
   string       id;
   int          kar, c;
   object obj;

   id = ob->name(); 
   if( query("id", ob) == "fish"){
   message_vision("$N説道：“哇，好大的魚！”\n",this_object()); 
   message_vision("$N説道：“多謝你啦，這個風箏送給你。”\n",this_object());
   obj=new("/quest/tulong/obj/kite");
   obj->move(this_player());
   return 1;
   }    
   message_vision("$N説道：＂多謝你啦!＂\n",this_object());
   if(id == "黃金" || id == "銀子"){
     kar = (int)who->query_kar();
     c = (int)ob->value();
     if(random(c) > random(10000*(1000-kar*2))) {
        addn("score", 1, who);
     }
   }
   return 1;
}
