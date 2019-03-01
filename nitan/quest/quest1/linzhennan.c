// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// linzhennan.c 林震南   

inherit NPC; 
#include <ansi.h>  
#include "biao.h"

mixed ask_biaodui();
mixed ask_yunbiao();
int   ask_fuwei();
int   ask_yuantu();
int   ask_pixie();
int   ask_tong();

void create()
{
        set_name("林震南", ({ "lin zhennan", "lin"}));
        set("gender", "男性");
        set("age", 65);
        set("title", "福威鏢局總鏢頭");
        set("long", "他就是福威鏢局總鏢頭－－林震南。\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);
        
        set_skill("force", 140);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set("inquiry", ([     
                "運鏢"     : (: ask_yunbiao :),
                "鏢隊"     : (: ask_biaodui :),  
                "鏢"       : (: ask_yunbiao :),
                "向陽老宅" : "林震南說道：那是我從前在福建時住的家院，已經破敗了。\n",
                "福威鏢局" : (: ask_fuwei :),
                "遠圖公"   : (: ask_yuantu :),
                "林遠圖"   : "林震南大怒：小孩子這麼沒禮貌，直呼先人名諱！\n",
                "辟邪劍法" : (: ask_pixie:),
                "銅錢"     : (: ask_tong:),
                "銅板"     : (: ask_tong:),
        ]));
        set_temp("apply/attack", 500);
        set_temp("apply/defense", 500);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_fuwei()
{
         say("林震南炫耀地說：我們林家三代走鏢，一來仗著先祖遠圖公當年闖下的威名，二\n"
                 "來靠著我們林家家傳的玩藝兒不算含糊，這才有今日的局面，成為大江以南首屈\n"
            "一指的大鏢局。江湖上提到『福威鏢局』四字，誰都要翹起大拇指，說一聲：『\n"
            "好福氣！好威風！』哈哈，哈哈！\n");
         set_temp("marks/林1", 1, this_player());
         return 1;
}

int ask_yuantu()
{
          if( query_temp("marks/林1", this_player()) )
          {
                 say("林震南磕一磕煙鬥，說道：遠圖公是我的祖父，福威鏢局是他一手創辦的。當年\n"
                        "祖父以七十二路辟邪劍法開創鏢局，當真是打遍黑道無敵手。其時白道上英雄見\n"
                          "他太過威風，也有去找他比試武藝的，青城派掌門余觀主的師父長青子少年之時\n"
                        "便在他辟邪劍法下輸了幾招。\n");
                 set_temp("marks/林2", 1, this_player());
                 return 1;
          }
          else 
          {
                 say("林震南說道：遠圖公是我的祖父。\n");
                 return 1;
          }
}

int ask_pixie()
{
          int p1, p2, p3, p4;
          if( query("passwd", this_player()) )
          {
                 say("林震南不悅地說道：我不是都告訴你了嗎？我的劍法不及先祖。\n");
          }
          else if( query_temp("marks/林2", this_player()) )
          {
                 say("林震南一驚，說道：你怎麼知道的？噢，我剛才說露嘴了。嗨，在下的功夫外人\n"
                          "不知底細，其實及不上先祖。。\n");
                 write("林震南頓一頓，接著對你低聲說：先祖去世前，曾給家父留下");
                 p1 = random(4) + 1;
                 p2 = random(4) + 1;
                 p3 = random(4) + 1;
                 p4 = random(4) + 1;
                 set("passwd", p1*1000+p2*100+p3*10+p4, this_player());
                 write(CHINESE_D->chinese_number(p1) + "千" + CHINESE_D->chinese_number(p2) +
                             "百" + CHINESE_D->chinese_number(p3) + "十" + CHINESE_D->chinese_number(p4));
                 write("個\n銅錢，我一直未解其中奧秘。\n");
          }
          else 
          {
                   message("vision",
                           HIM "林震南勃然大怒，喝道：你也窺視我們林家的辟邪劍譜？！我跟你拼了！\n" NOR, 
                           environment(), this_object());
                   kill_ob(this_player());
          }
          delete_temp("marks/林1", this_player());
          delete_temp("marks/林2", this_player());
          return 1;
}

int ask_tong()
{
          int p, p1, p2, p3, p4;
          if( !(p=query("passwd", this_player())) )
          {
                 say("林震南一臉譏笑的樣子，說：怎麼混到這一步了到處要錢？\n");
          }
          else 
          {
                 write("林震南低聲說：先祖去世前，曾給家父留下");
                 p1 = (int)p / 1000;
                 p2 = (int)(p - p1 * 1000) / 100;
                 p3 = (int)(p - p1 * 1000 - p2 * 100) / 10;
                 p4 = (int)(p - p1 * 1000 - p2 * 100 - p3 * 10);
                 write(CHINESE_D->chinese_number(p1) + "千" + CHINESE_D->chinese_number(p2) +
                             "百" + CHINESE_D->chinese_number(p3) + "十" + CHINESE_D->chinese_number(p4));
                 write("個\n銅錢，我一直未解其中奧秘。\n");
          }
          return 1;
}

string chinese_time(int t)
{
        int d, h, m, s;
        string time;
        s = t % 60;     t /= 60;
        m = t % 60;     t /= 60;
        h = t % 24;     t /= 24;
        d = t;
        if (d) time = chinese_number(d) + "天";
        else time = "";
        if (h) time += chinese_number(h) + "小時";
        if (m) time += chinese_number(m) + "分";    
        time += chinese_number(s) + "秒";
        return time;
}

mixed ask_yunbiao()
{
            int time;
            object me, biaoche;
            mapping biao;

            me = this_player();

        if( count_lt(query("combat_exp", me),100000) )
                      return "運鏢可是件危險的差使，還是練好了功夫再來吧！\n";    
                      
            if( query_temp("quest_yunbiao/have_task", me) )
                       return "你上次的鏢還沒送到呢，怎麼又來了？\n"; 

/*
            if( query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/finished_time", me))<20 )
                       return RANK_D->query_respect(me) + "辛苦了，現在沒有鏢車要運，過會再來吧！\n";
*/

            if( mapp(query_temp("quest_yunbiao", me) )
         && !query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "你把我的鏢弄哪裡去啦？不是被人劫了吧？\n";

            biao = yun_biao[random(sizeof(yun_biao))];
            time = biao["time"];
            
            delete_temp("quest_yunbiao", me);
            set_temp("quest_yunbiao/name", biao["name"], me);
            set_temp("quest_yunbiao/file", biao["file"], me);
            set_temp("quest_yunbiao/bonus", biao["bonus"], me);
            set_temp("quest_yunbiao/time", biao["time"], me);
            set_temp("quest_yunbiao/start_time", time(), me);
            set_temp("quest_yunbiao/have_task", 1, me);

            biaoche = new(__DIR__"biaoche");
            set("time", time, biaoche);
            set("file", biao["file"], biaoche);
            biaoche->start_escape_me();
            set("owner",query("id",  me), biaoche);
            set("owner_name",query("name",  me), biaoche);
            biaoche->move(environment(me));
            
        /*
             message("channel:rumor",HIM"【鏢局傳聞】"+query("name", me)+
                     "即將護送鏢車起程前往" + biao["name"] + "！\n" NOR,
                     users());  
        */
        
            delete_temp("apply/short", me);
            me->set_temp("apply/short",
                            ({HIM"福威鏢局鏢頭"NOR+me->name()+"("+query("id", me)+")"}));

            message_sort(HIM "$N" HIM "對$n" HIM "吩咐道：請在" + chinese_time(time) + "內，將鏢車運送到" +
                     biao["name"] + "。一路多加小心，你還是趁早上路吧！\n" NOR, this_object(), me);
        return 1;
}


mixed ask_biaodui()
{
            int time, i;
            object me, parter, biaoche, *team;
            mapping biao;

            me = this_player();

        if( count_lt(query("combat_exp", me),200000) )
                      return "運鏢可是件危險的差使，還是練好了功夫再來吧！\n";
                      
            if (! pointerp(team = me->query_team()))
                       return "鏢隊需要人多一點才有保障，多叫些人手來吧！\n";

            i = sizeof(team);
            if (i > 2) return "人多手雜，容易壞事！\n";

            if (objectp(team[0]) && objectp(team[1]))
            {
                     if(team[0] == me) parter = team[1];
                     else parter = team[0];
            }

            if (! objectp(parter) 
         || !present(query("id", parter),environment(me)) )
                       return "還是約上你的同伴一起來吧！\n";

            if( query_temp("quest_yunbiao/have_task", me) )
                       return "你們上次的鏢還沒送到呢，怎麼又來了？\n";

            if( mapp(query_temp("quest_yunbiao", me) )
         && !query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "你把我的鏢隊弄丟了，居然還有臉回來見我？\n";

        if( count_lt(query("combat_exp", parter),50000) )
                      return "運鏢可是件危險的差使，不要讓你的同伴去送死了！\n";
                      
            if( mapp(query_temp("quest_yunbiao", parter) )
         && !query_temp("quest_yunbiao/finished_time", parter )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "你找這樣無能的同伴當幫手，我可不放心把鏢隊交給你！\n";

            biao = yun_biao[random(sizeof(yun_biao))];
            time = biao["time"];
            
            delete_temp("quest_yunbiao", me);
            set_temp("quest_yunbiao/name", biao["name"], me);
            set_temp("quest_yunbiao/file", biao["file"], me);
            set_temp("quest_yunbiao/bonus", biao["bonus"], me);
            set_temp("quest_yunbiao/time", biao["time"], me);
            set_temp("quest_yunbiao/start_time", time(), me);
            set_temp("quest_yunbiao/have_task", 1, me);

        delete_temp("quest_yunbiao", parter);
            set_temp("quest_yunbiao/name", biao["name"], parter);
            set_temp("quest_yunbiao/file", biao["file"], parter);
            set_temp("quest_yunbiao/bonus", biao["bonus"], parter);
            set_temp("quest_yunbiao/time", biao["time"], parter);
            set_temp("quest_yunbiao/start_time", time(), parter);
            set_temp("quest_yunbiao/have_task", 1, parter);

            biaoche = new(__DIR__"da_biaoche");
            set("time", time, biaoche);
            set("file", biao["file"], biaoche);
            biaoche->start_escape_me();
            set("owner",query("id",  me), biaoche);
            set("parter",query("id",  parter), biaoche);
            set("owner_name",query("name",  me), biaoche);
            biaoche->move(environment(me));

        /*
            message("channel:rumor",HIM"【鏢局傳聞】"+query("name", me)+
                     "率領的鏢隊即將起程前往" + biao["name"] + "！\n" NOR, users());
        */
        
            delete_temp("apply/short", me);
            me->set_temp("apply/short",
                         ({HIM"福威鏢局鏢頭"NOR+me->name()+"("+query("id", me)+")"}));

            delete_temp("apply/short", parter);
            parter->set_temp("apply/short",
                             ({HIM"福威鏢局鏢師"NOR+parter->name()+"("+query("id", parter)+")"}));

            message_sort(HIM "$N" HIM "對$n" HIM "吩咐道：請在" + chinese_time(time) + "內，將鏢隊運送到" +
                     biao["name"] + "。一路多加小心，你們還是趁早上路吧！\n" NOR, this_object(), me);
        return 1;
}

void die()
{
        this_object()->recover();  
        return; 
}

void unconcious()  
{
        this_object()->recover();  
        return; 
}