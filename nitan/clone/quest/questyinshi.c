// /clone/quest/questyinshi.c
//// Last Modified by sir on 4.20.2002

#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string *msg_dunno = ({
        "$n搖搖頭，說道：沒聽說過。\n",
        "$n疑惑地看著$N，搖了搖頭。\n",
        "$n睜大眼睛望著$N，顯然不知道$P在說什麼。\n",
        "$n聳了聳肩，很抱歉地說：無可奉告。\n",
        "$n說道：嗯....這我可不清楚，你最好問問別人吧。\n",
        "$n想了一會兒，說道：對不起，你問的事我實在沒有印象。\n"
});
string *reject_msg = ({
        "說道：您太客氣了，這怎麼敢當？\n",
        "像是受寵若驚一樣，說道：請教？這怎麼敢當？\n",
        "笑著說道：您見笑了，我這點雕蟲小技怎夠資格「指點」您什麼？\n"
});
string * name_msg = ({
        "書生",
        "客商",
        "錦衣衛士",
        "採藥人",
        "江湖藝人",
        "進香客",
        "挑夫",
        "家丁",
        "大漢",
        "官兵",
        "賣花姑娘",
        "趟子手",
        "乞丐",
        "小販",
        "刀客",
        "劍客",
        "吃客",
        "遊方和尚",
        "遊方道人",
        "江湖豪客",
});
string * long_id = ({
        "shu sheng",
        "ke shang",
        "wei shi",
        "caiyao ren",
        "jianghu yiren",
        "jinxiang ke",
        "tiao fu",
        "jia ding",
        "da han",
        "guan bing",
        "flower girl",
        "tangzi shou",
        "qi gai",
        "xiao fan",
        "dao ke",
        "jian ke",
        "chi ke",
        "seng ren",
        "dao ren",
        "jianghu haoke",
});

void create()
{
        int i;
        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({ long_id[i]}) );
        set("gender", random(2)>0 ? "女性" : "男性" );
        set("attitude", "friendly");
        set("chat_chance", 60);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );
        set("inquiry", ([
                "隱士"    : (: ask_me :),
                "歸隱"    : (: ask_me :),
                "yinshi" : (: ask_me :),
                "guiyin"  : (: ask_me :),
        ]) );
        set("no_steal", 1);
        set("ask_time",0);
        set("yinshi", 1 );
        set("owner","mud_os");
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
        carry_object("/clone/food/jiudai");
}
                        
int ask_me(object who)
{
        object ob = this_object(), me = this_player();
        mapping map_status, skill_status,hp_status,skl;
        string *sname,*mname;
        string *skillname;
        int i,j,skilllvl,topexp;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});

        if( query("ask_time", ob)<2 )
          {
            message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
            addn("ask_time", 1, ob);
           }
           
        else if( query("ask_time", ob) == 2 )
           {
            message_vision(HIC"$N眼中寒光一閃，馬上又變得漠然了，只是奇怪地看著$n。\n"NOR, ob, me);
            set("owner",query("id",  me), ob);
            addn("ask_time", 1, ob);
           }   

        else if( query("ask_time", ob) == 3 && query("family_name", ob) != query("family/family_name", me) )
        {
              hp_status = me->query_entire_dbase();              
        
              addn("ask_time", 1, ob);
              set("str", hp_status["str"], ob);
              set("int", hp_status["int"], ob);
              set("con", hp_status["con"], ob);
              set("dex", hp_status["dex"]+10, ob);
              set("age", hp_status["age"]+2, ob);

              set("max_jing", hp_status["max_jing"]*3/2, ob);
              set("eff_jing", hp_status["max_jing"]*3/2, ob);
              set("jing", hp_status["jing"]*3/2, ob);
              if ((hp_status["max_qi"]*2)<1500)
                { 
                  set("max_qi", 1500, ob);
                  set("eff_qi", 1500, ob);
                  set("qi", 1500, ob);
                 }  
              else                
                {
                  set("max_qi", hp_status["max_qi"]*2, ob);
                  set("eff_qi", hp_status["max_qi"]*2, ob);
                  set("qi", hp_status["max_qi"]*2, ob);
                 }
              if ((hp_status["max_neili"])<1500)
                 {
                   set("max_neili", 1500, ob);
                   set("neili", 1500, ob);
                   set("jiali", 50, ob);
                  }
              else 
                 { 
                  set("max_neili", hp_status["max_neili"], ob);
                  set("neili", hp_status["max_neili"], ob);
                  set("jiali", hp_status["max_neili"]/30, ob);
                 }
              topexp=query("combat_exp", me);
              set("combat_exp", topexp*3/2+100, ob);
              set("no_check", 1, ob);
              skl = me->query_skills();
              skilllvl=200;        
              if (sizeof(skl))
              {
                skillname = sort_array( keys(skl), (: strcmp :) );
                for (j=0; j<sizeof(skl); j++)
                {
                        if (skilllvl < skl[skillname[j]])
                                skilllvl = skl[skillname[j]];
                }                                
              }
              if (skilllvl>=300)  skilllvl=skilllvl*5/6;
              skill_status = ob->query_skills();
              sname = keys(skill_status);
              for(i=0; i<sizeof(skill_status); i++)
                {
                        ob->set_skill(sname[i], skilllvl);
                }
                
                message_vision(HIC"$N嘆了口氣，說道：“我已歸隱多年，你卻還要苦苦相逼？”\n"NOR, ob, me);       
                message_vision(HIY"$N眼中突然閃過一道寒光，憤怒地瞪著$n，大聲喝道："+RANK_D->query_self_rude(ob)+"就是"+query("fname", ob)+"！"+RANK_D->query_rude(me)+"！納命來吧！\n"NOR,ob,me);
                me->start_busy(1);      
                addn_temp("apply/dodge", 150, ob);
                addn("yinshi", 1, ob);
                set("title",query("family_name",  ob)+"隱士", ob);
                set("name",query("fname",  ob), ob);
                if ( mapp(map_status = ob->query_skill_map()) )
                {
                        mname  = keys(map_status);
                        for(i=0; i<sizeof(map_status); i++) 
                     {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set( "chat_chance_combat", 60);         
                set( "chat_msg_combat", combat_actions );               
                fight_ob(me);
                addn("ask_time", 1, ob);

        }
        else if( query("ask_time", ob) >= 3 && query("family_name", ob) == query("family/family_name", me )
                 && query("owner", ob) == query("id", me) )
                message_vision(HIG"$N嘆了口氣，看著$n笑道：“原來是同門後輩，你這麼辛苦地找我，所為何事？”。\n"NOR, ob, me);
        else message_vision(HIG"$N嘆了口氣，看著$n苦笑道：“你這麼辛苦地找我，所為何事？”。\n"NOR, ob, me);
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        if( query("no_fight", find_object(dest)))return 0;
        if( this_object()->is_fighting() ) return 0;
        command("go " + dir);
        return 1;
}

void init()
{
         add_action("do_hit","hit");
         add_action("do_hit","kill");    
         add_action("do_hit","touxi");
         add_action("do_hit","ansuan");
         add_action("do_hit","steal");   
         add_action("do_halt","halt");
         add_action("do_halt","go");
         add_action("do_halt","surrender");
         add_action("do_qingjiao","qingjiao");
         add_action("do_look","look");
}
int do_look(string arg)
{
        object ob = this_object();
        object me = this_player();
        if( !arg || arg != query("id", ob) )
                return 0;

        if( query("yinshi", ob) == 1 )
         {
          message_vision("你想看清對方的樣子，可卻怎麼也無法做到！\n",me);
          return 1;        
         }
        else return 0;

}
int do_qingjiao(string arg)
{  
     object ob = this_object(), me =this_player();
     string special;
     int bl,sl,i;
   
      if (!living(me)||!living(ob)) return 0;
      if (me->is_busy() || me->is_fighting())
                 return notify_fail("你正忙著呢。\n");
      if (ob->is_fighting())
          return notify_fail("對方正忙著呢。\n");
      if( query("ask_time", ob)<3 )
          {
            message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);           
           }
      else if( query("owner", ob) != query("id", me )
              || query("family_name", ob) != query("family/family_name", me) )
          {
             return  notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );
          }   
      else{     
           if (!arg) return notify_fail("你要請教什麼？\n");
           if (!(special=me->query_skill_mapped(arg)))
                return notify_fail("你只能從特殊技能中請教基本技能。\n");
           bl=me->query_skill(arg,1);
           sl=me->query_skill(special,1);
           i=random(10);
           message_vision(HIG"$N哈哈笑道：“你我既是同門，今日相見也算有緣，好吧我就告訴你些本門武功心得！”。\n"NOR, ob, me);
           if( i<3 )
           { 
             write(HIM"你聽了指導，瞑思苦想，對"+to_chinese(arg)+"的體會又深了一層。\n"NOR);
             me->set_skill(arg,bl+1);
            }
           else 
           { 
             write(HIR"你聽了指導，瞑思苦想，對"+to_chinese(special)+"的體會又深了一層。\n"NOR);
             me->set_skill(special,sl+1);
            }
           addn("score", 1000+random(500), me);
           me->start_busy(1);
           message_vision(HIG"$N嘆了口氣，說道：“你我若是有緣，來日自會再聚，時候不早了，我先走一步!”。\n"NOR, ob, me);
           destruct(ob);
        }
} 
           
int do_hit(string arg)
{
        object ob = this_object();
        object me = this_player();
        mapping map_status;
        string* mname;
        int i,j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});
        if( !arg || arg != query("id", ob) )
                return 0;
         
        //if (!ob->query("owner"))
        if( (query("id", me) == query("owner", ob)) && (query("ask_time", ob) == 3) )
             return notify_fail("你我無冤無仇，你這又是何必呢？\n");
 
       else if( query("ask_time", ob)>3 && query("family_name", ob) == query("family/family_name", me )
            && query("owner", ob) == query("id", me) )
           return notify_fail("你既然已找到本門前輩，還不趁此大好機會討教武功？\n");
           
        else if( query("ask_time", ob)>3 )
        {
                if ( mapp(map_status = ob->query_skill_map()) )
                {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) 
                      {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set("chat_chance_combat", 60, ob);
                set("chat_msg_combat", combat_actions, ob);
                if( query("combat_exp", me)>query("combat_exp", ob) )
                  set("combat_exp",query("combat_exp",  me), ob);
                kill_ob(me);    
        }
}

int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if( me->is_fighting(ob) && query("ask_time", ob) >= 3 )
        {
                message_vision(HIW"$N喝道：“你既然識破我的身份，就休想活著離開！”\n"NOR, ob, me);
                return 1;
        }
        return 0;
}
void die()
{
        object ob = this_object();
        object me,fme;
        int pot,exp,score;
        me = query_temp("last_damage_from");
        fme=query_temp("last_opponent");          
  
         if( fme && 
             query("ask_time", ob)>3 && query("owner", ob) == query("id", me )
              && query("owner", ob) == query("id", fme )
              && query("family_name", ob) != query("family/family_name", me) )
            {
              pot = 400+random(400);
              exp = 1500+random(500);
              score =300+random(50);
              addn("combat_exp", exp, me);
              addn("potential", pot, me);
              addn("score", score, me);
              tell_object(me,HIW"你在尋訪過程中得到如下獎勵：\n");
              tell_object(me,chinese_number(exp) +"點實戰經驗\n" +
              chinese_number(pot) + "點潛能\n" +
              chinese_number(score)+"點江湖閱歷\n"NOR);
              }
         ::die();    
}