// /clone/quest/questjianxi.c
//last modified by sega 13/4/2000
// Modified by Zeratul Jan 5 2001

//修改成不能幫忙殺
#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string * name_msg = ({
        "流氓",
        "進香客",
        "挑夫",
        "家丁",
        "官兵",
        "賣花姑娘",
        "趟子手",
        "小販",
        "刀客",
        "劍客",
        "遊方和尚",
        "江湖豪客",
});

string * long_id = ({
        "liu mang",
        "jinxiang ke",
        "tiao fu",
        "jia ding",
        "guan bing",
        "flower girl",
        "tangzi shou",
        "xiao fan",
        "dao ke",
        "jian ke",
        "seng ren",
        "jianghu haoke",
});

void create()
{
        int i;
        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({ long_id[i]}) );
        set("gender", random(2)>0 ? "女性" : "男性" );
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );
               set("inquiry", ([
                "姦細"    : (: ask_me :),
                "jian xi" : (: ask_me :),
                "jianxi"  : (: ask_me :),
        ]) );
        set("no_steal", 1);
//      set("ask_time", 0);
        set( "jianxi", 1 );
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
//        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/food/jiudai");
  if (clonep())
   call_out("dest_me",1200,this_object());
}
int ask_me(object who)
{
        object ob = this_object(), me = this_player();
        mapping map_status;
        string*        mname;
        int i,j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});

        if( query("owner", this_object()) == query("id", me) )
        {
                message_vision(HIY"$N眼中突然閃過驚懼的目光，雙眼冒火般瞪著$n，大聲喊道："+RANK_D->query_self_rude(ob)+"就是"+query("fname", ob)+"！"+RANK_D->query_rude(me)+"！納命來吧！\n"NOR,ob,me);
                me->start_busy(1);        
    ob->fight_ob(me);         
//                me->fight_ob(ob);        
                if( query_temp("asked", ob))return 1;
                if( query("combat_exp", me)>10000000 )
                        addn_temp("apply/dodge", 250, ob);
    else if( query("combat_exp", me)>5000000 )
      addn_temp("apply/dodge", 200, ob);
    else if( query("combat_exp", me)>3000000 )
      addn_temp("apply/dodge", 150, ob);
    else if( query("combat_exp", me)>1000000 )
      addn_temp("apply/dodge", 100, ob);
    else 
      addn_temp("apply/dodge", 50, ob);
                set("title",query("family_name",  ob)+"姦細", ob);
                set("name",query("fname",  ob), ob);
                if ( mapp(map_status = ob->query_skill_map()) ) {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) {
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
    set_temp("asked", 1, ob);
        }
        else
                message_vision(HIY"$N眼中寒光一閃，馬上又變得漠然了，只是奇怪地看著$n。\n"NOR, ob, me);
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
         add_action("do_halt","halt");
         add_action("do_halt","go");
         add_action("do_halt","surrender");
}
int accept_hit(object me)
{
        notify_fail(HIW"不是你要抓的人，湊什麼熱鬧！\n"NOR);
        if( query("owner", this_object()) == query("id", me )
         && query_temp("asked", this_object()) )
        {
                me->kill_ob(this_object());
                return 1;
        }
        return 0;
}
int accept_fight(object who)        {return accept_hit(who);}
int accept_kill(object who)                {return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)        {return accept_hit(who);}

int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if ( me->is_fighting(ob)  )
        {
                tell_object( me, HIR"姦細未除，怎能臨陣退縮？\n"NOR );
                return 1;
        }
        return 0;
}

void dest_me(object ob)
{
        message_vision("只見$N忽然急轉身行，縱身鑽進行人中，轉眼就蹤跡皆無。\n",ob);
        destruct(ob);
}