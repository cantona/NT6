//meipo.c

#include <ansi.h>
inherit NPC;

string ask_hunyin();

void create()
{
      set_name("媒婆",({"meipo", "mei po", "po", "mei"}));
      set("age", 65);
      set("gender", "女性");
      set("nickname", "姻緣天定");
      set_skill("unarmed", 40);

      set("inquiry",([
            "介紹對象" :  (: ask_hunyin :),
      ]));

        set("chat_chance", 15); 
        set("chat_msg", ({ 
                "花媒婆神祕兮兮的説道：據説靈山上有傳説中的雪蓮花，那可是送給心上人最好的禮物哦。\n",
                "花媒婆訕訕的説：這個～～他是個瘸子，老婆子我可沒説他不是啊，這嫁都嫁了，還能怪我？\n",
                "花媒婆偷偷一笑：這雪蓮花戴上了真是花容月貌啊，我老婆子可要想個法子留下，不能就這麼給了那小娘子。\n"
        }) ); 

      setup();
      carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
      object ob;

      ::init();

      if (interactive(ob=this_player())&&!is_fighting())
      {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
      }
      add_action("do_agree", "agree");
}

void greeting(object ob)
{
      if (!ob||environment(ob)!=environment())   return;
      if( query("age", ob) >= 18 && !query("couple", ob) )
      {
           if( query("gender", ob) == "無性" )
           {
                 message_vision("$N對$n搖頭歎道：可惜是個太監，不然也到" +
                                "娶媳婦的時候了。\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "男性" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N看見$n，嚇了一跳：這位公子可是要老婆子" +
                                "給你介紹對象？難哪！\n", this_object(), ob);
                 else

                 message_vision("$N湊上前對$n道：公子一表人材，可要老婆子" +
                                "給你介紹對象？\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "女性" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N看見$n，歎了口氣：這位姑娘雖不愁嫁，可要找" +
                                "個好人家卻非易事！\n", this_object(), ob);
                 else

                 message_vision("$N湊上前對$n道：好俊俏的人兒，可要老婆子" +
                                "給你介紹對象？\n", this_object(), ob);
                 return;
           }
      }
      return;
}

string ask_hunyin()
{
      object *list = users();
      object ob = this_player();
      string who,gender=query("gender", ob);
      int i, p;

      if (gender == "無性")
           return "你個死太監，還想找對象結婚害人？";

      if( query("couple", ob) )
           return "你都是結了婚的人了, 還找什麼對象？";

      if( query("age", ob)<18 )
           return "這麼小就想找對象啦，嘻嘻。\n";

      if( query_temp("mameipo/agree", ob) )
           return "怎麼？"+query_temp("mameipo/agree", ob)+
                  "還沒有答應你這門親事嗎？\n";

      i = 0;
      while ( i <sizeof(list))
      {
           if( query("gender", list[i]) == gender || 
               query("gender", list[i]) == "無性" || 
               query("age", list[i])<18 || 
               query("age", list[i])>query("age", ob)+5 || 
               query("age", list[i])<query("age", ob)-5 || 
               query("class", list[i]) == "bonze" || 
               query("couple", list[i]) )
           list[i] = 0;
           i++;
      }

      list -= ({ 0 });
      if ( sizeof(list) > 0 )
      {
           p = random(sizeof(list));
           who=query("id", list[p]);
           set_temp("mameipo/who", who, ob);
           return "看來"+query("name", list[p])+"("+query("id", list[p])+")"+
                  "和你很相配，你意下如何？(agree)\n";
      }
      else   return "暫時還找不到與你相配的人。";
}

int do_agree()
{
      object who, ob = this_player();

      if( !query_temp("mameipo/who", ob) )
      {
           tell_object(ob, "花媒婆對你道：你是想老婆子給你介紹對象麼？\n");
           return 1;
      }

      tell_object(ob, HIC"花媒婆對你道：既如此，老婆子就給你把這好事兒跟對方説説。\n"NOR);
      who=find_player(query_temp("mameipo/who", ob));
      if (!who)
      {
           tell_object(ob,HIC"花媒婆對你道：可惜，現在老婆子找不到你的意中人。\n"NOR);
           return 1;
      }

      tell_object(who,query("name", ob)+"託花媒婆給你送來朵"+HIR+"紅玫瑰"NOR+"。\n");
      command("tell"+query_temp("mameipo/who", ob)+""+query("name", ob)+"("+
              query("id", ob)+")對你很有意思，託老婆子給你説説。\n");
      new("/d/city/obj/rrose")->move(who);
      tell_object(ob, HIC"花媒婆對你道：老婆子已經把你的意思轉告了，你這就去提親吧。\n"NOR);
      delete_temp("mameipo/who", ob);
      set_temp("mameipo/agree",query("name",  who)+"("+query("id", who)+")", ob);
      return 1;
}
