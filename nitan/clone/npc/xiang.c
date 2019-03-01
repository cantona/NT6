// lady1.c

#include <ansi.h>
inherit NPC;
object ob;
int is_ename(string id);
int is_cname(string name);

void create()
{
        set_name("項長老", ({"xiang zhanglao", "xiang", "zhanglao"}));
        set("nickname", "丐幫六老");
        set("gender", "男性");
        set("age", 59);
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);
        set("long", 
"這是丐幫的傳功長老，也負責收集各地弟子打聽到的各種小道消息。\n"+
"天下之大，沒有他不知道的人物。\n");
        
        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        
        set("combat_exp", 1500000);
        set("score", 200000);
        set("shen", 100000);
         
        set_skill("force", 150);             // 基本內功
        set_skill("huntian-qigong", 150);    // 混天氣功
        set_skill("dodge", 150);                   // 基本躲閃
        set_skill("xiaoyaoyou", 150);        // 逍遙遊
        set_skill("parry", 150);             // 基本招架
        set_skill("hand", 150);              // 基本手法
        set_skill("suohou-hand", 150);       // 鎖喉擒拿手
        set_skill("blade", 150);             // 基本刀法
        set_skill("liuhe-dao", 150);       // 四象六合刀
        set_skill("begging", 100);           // 叫化絕活
        set_skill("checking", 100);          // 道聽途說
        set_skill("training", 100);          // 馭獸術
        
        map_skill("force", "huntian-qigong");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        prepare_skill("hand",  "suohou-hand");

        set("party/party_name", HIC"丐幫"NOR);
        set("party/rank", RED"九袋長老"NOR);
        set("party/level", 9);
        create_family("丐幫", 10, "傳功長老");

        setup();
        
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object("kungfu/class/gaibang/obj/cloth")->wear();
}



int accept_ask(object ob, string topic)
{
        object fob;
        object *livings;
                                int i;
                                
        if( topic == query("id", ob) || topic == query("name", ob) )
        {
                command("laugh"+query("id", ob));
                return 1;
        }
     if( is_cname(topic) && !(query_temp("pay_for_ask", ob)) )
       {
               set_temp("give_for_ask", 1, ob);
        set_temp("pending/ask_value", 10000, ob);
               command("say 重名的人可多著呢，我得多花點心思，先拿點黃金出來。");
        return 1;
      }
      
      if( is_cname(topic) && query_temp("pay_for_ask", ob) )
      {
              livings=livings();
              for (i=sizeof(livings)-1;i>=0;i--)
               {
                       if( (query("name", livings[i]) == topic || query("fname", livings[i]) == topic) && environment(livings[i]) )
                         {
                                 fob=livings[i];
                           break;
                         }
               }
              if (!fob)
                                {
//                command("shake");
//          command("say 我從沒聽說過江湖上有這號人物。");
//          return 1;
            return 0;
        }
        delete_temp("pay_for_ask", ob);
      }
      
      if (is_ename(topic))
      {
        fob = find_player(topic);
        if (! fob || ! ob->visible(fob) ) 
        fob = find_living(topic);
        if (! fob || ! ob->visible(fob) )
        {
//                command("shake");
//          command("say 我從沒聽說過江湖上有這號人物。");
//          return 1;
            return 0;
        }
        if ( ! environment(fob) )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "小"
                               "聲道：好像是聽說有這麼個人物，不過沒有弟子向我匯報過他的行蹤。\n" NOR, this_object(), ob);
                return 1;
                
        }
      }
      if (!is_ename(topic) && !is_cname(topic))
        return 0;
      if (!environment(fob) || explode(file_name(environment(fob)),"/")[0]!="d")
              return 0;
         
//        if ( !ob->query("know_ask_cheap") ||ob->query("ask_cheap")   )
          if( !query("owner", fob) && !userp(fob) )
        {
//                      ob->set("know_ask_cheap",1);
                set_temp("pending/ask_about", topic, ob);
                if (!objectp(fob))
                {
                  command("slap");
                  return 1;
                }
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 2000, ob);
                message_vision(CYN "$N" CYN "皺了皺眉頭，對$n" CYN "搖搖"
                               "頭道：看來你這次確實是遇到了困難，收你二十"
                               "兩白銀就是了。\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && !query("level", fob) )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 30000, ob);
                message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n" CYN "小"
                               "聲道：沒有問題，不過得要三兩黃金，不二"
                               "價！\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && query("level", fob)<3 )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 1000, ob);
                message_vision(CYN "$N" CYN "皺了皺眉頭，對$n" CYN "搖搖"
                               "頭道：看來你這次確實是遇到了困難，收你十"
                               "兩白銀就是了。\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && query("level", fob) >= 3 )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 100000, ob);
                message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n" CYN "小"
                               "聲道：沒有問題，不過得要十兩黃金，不二"
                               "價！\n" NOR, this_object(), ob);
                return 1;        
        } else if (userp(fob))
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 1000000, ob);
                message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n" CYN "小"
                               "聲道：找玩家也沒有問題，不過得要一百兩黃金，不二"
                               "價！\n" NOR, this_object(), ob);
                return 1;
        }
}

int accept_object(object me, object ob)
{
           string wid;
           object fob;
           int va;
           string old_fob;
           int flag;
           string env;
           string str;
        if (clonep(this_object()))
        {
                command("hehe");
                command("say 俺是真的項長老，如假包換啊！");
                return 1;
        }
     if( !stringp(query("money_id", ob)) )
     {
        switch(query_temp("beichou_refused", me) )
        {
          case 0:
                command("heihei");
                command("say 這種破爛你留著吧。");
                set_temp("beichou_refused", 1, me);
                return 0;

          case 1:
                 message_vision(HIC "$N" HIC "飛起一腳，把$n"
                                HIC "踢了出去，罵道：搗什麼亂"
                                "？\n" NOR,this_object(), me);
                 break;

          case 2:
                 message_vision(HIC "$N" HIC "飛起一腳，狠狠"
                                "的把$n" HIC "踢了出去，罵道："
                                "居然還敢來搗亂？\n" NOR,
                                this_object(), me);
                 me->receive_damage("qi", 100);
                 me->receive_wound("qi", 10);
                 break;

          default:
                 message_vision(HIC "$N" HIC "大怒，一招飛龍"
                                "在天，就見$n" HIC "像紙片一"
                                "樣飛了出去。\n" NOR,
                                this_object(), me);
                 command("chat*kick4"+query("id", me));
                 me->unconcious();
                 break;
         }

         addn_temp("beichou_refused", 1, me);
         me->move("/d/city/shilijie5");
         message_vision(HIC "只聽“啪嗒”的一聲，$N" HIC
                        "狠狠的摔在了地上。\n" NOR, me);
                return 0;
     }
     delete_temp("beichou_refused", me);
           va=query_temp("pending/ask_value", me);
           if (wizardp(me)) va = 1;
            if( query_temp("give_for_ask", me) && ob->value() >= va )
            {
       delete_temp("give_for_ask", me);
       set_temp("pay_for_ask", 1, me);
                     command("say 好吧，說說你想找誰。");
                     return 1;
           }
     if( stringp(wid=query_temp("pending/ask_about", me)) )
     {
              if (ob->value() < va)
        {
            message_vision(CYN "$N" CYN "冷笑一聲道：就這點錢？"
                               "打發店小二還差不多。\n" NOR,
                               this_object());
            return 0;
        }
        delete_temp("pending/ask_about", me);
        old_fob=query_temp("pending/ask_who", me);
        flag=1;
        if (!stringp(old_fob) || !objectp(fob=find_object(old_fob)) || !me->visible(fob) || !environment(fob) )
        {
                        message_vision(CYN "$N" CYN "撓撓頭對$n" CYN "道：怪事…剛"
                                       "才我還有他的消息呢，怎麼這麼一會兒。\n" NOR,
                                       this_object(), me);
                        return 0;            
            }
//          destruct(ob);
          if (!objectp(fob))
          {
                  command("say 好像有點問題，問一下巫師吧。");
            return 1;
          }
          env=file_name(environment(fob));
          if (sscanf(env,"/d/%s/%*s",env)!=2) 
          {
             message_vision(CYN "$N" CYN "撓撓頭對$n" CYN "道：怪事…剛"
                           "才我還有他的消息呢，怎麼這麼一會兒。\n" NOR,
                           this_object(), me);
                        return 0;
          }
          
          env=to_chinese(env);
          if (strsrch(env,"/")>0 || is_ename(env))
            env="某個地方";
//          command("whisper " + me->query("id") +" 剛剛有弟子前來報告：");     
          log_file("xiang",me->name()+"詢問"+fob->name()+"("+query("id", fob)+")\n");

          str = this_object()->name()+"在你的耳邊悄聲說道："+fob->name()+"剛才在";
          if( stringp(query("place", fob)) )
                  str += env+"的";
          str+=query("short", environment(fob))+"附近出沒。\n";

          tell_object(me,str);
 //         if (va <= 2000)
 //               me->add("ask_cheap", -1);
 //         else me->set("ask_cheap", 3);
          return 1;
        }
        
        if (ob->value() )
        {
                message_vision(CYN "$N" CYN "接過$n" CYN "遞過去的" + ob->name() +
                               NOR + CYN "，皺了皺眉，道：你有錢沒地方花啊？算了，你不要就"
                               "給我吧！\n" NOR, this_object(), me);
                return 1;
        }
        return 1;
}

int is_ename(string id)
{
        int i;

        id = replace_string(id,"'s betrayer","");
        if (strsrch(id," ")==-1)
        if( strlen(id) < 3 || strlen(id) > 12  ) 
                        return 0;
        id = replace_string(id," ","");
        i = strlen(id);
        while(i--)
          if( id[i]<'a' || id[i]>'z')
            return 0;
//        tell_object(find_player("qingyun"),"is ename\n");
        return 1;
}

int is_cname(string name)
{
        int i;

        i = strlen(name);
        
        if( strlen(name) < 4 || strlen(name) > 10  ) 
                return 0;
        if( strsrch(name, "　") >= 0) 
                return 0;
        while(i--) {
                if( name[i]<=' ' ) 
                   return 0;
                if( i%2==0 && !is_chinese(name[i..<0]) )                        
                   return 0;
        }

        return 1;
}
