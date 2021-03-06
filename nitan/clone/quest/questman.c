// /clone/quest/questman.c
// Modified by Zeratul Jan 5 2001

#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int set_perform();
void create()
{
        set_name("  ", ({ "betrayer" }));
        set("attitude", "friendly");

        set("chat_chance", 40);
        set("chat_msg", ({
                (:call_out,"random_move",0:),
        }) );
        set("no_steal", 1);
        set("quest_no_guard",1);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :)
                }));
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
        if (clonep())
          call_out("dest_me",1200,this_object());
//        carry_object("/clone/weapon/changjian")->wield();
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;

        if( !exits=query("exits", environment(this_object())))return 0;
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
         add_action("do_halt","surrender");
   add_action("do_halt","go");
         if (!query("inited")) set_perform();
//         add_action("do_halt","jiasi");
}

int accept_hit(object me)
{
        if( query("owner", this_object()) == query("id", me))return 1;
        else return notify_fail(HIW"不是你要抓的人，湊什麼熱鬧！\n"NOR);
}
int accept_fight(object who)        {return accept_hit(who);}
int accept_kill(object who)                {return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)        {return accept_hit(who);}
int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if ( me->is_fighting(ob) )
        {
                message_vision(HIW"$N喝道：“你既然識破我的身份，就休想活着離開！”\n"NOR, ob, me);
                return 1;
        }
        return 0;
}
int set_perform()
{
        object ob = this_object(), me = this_player();
  mapping map_status;
  string*        mname;
  int i,j;
  mixed perform_actions = ({});
  mixed combat_actions = query("chat_msg_combat");
  mixed msg =({});
        set("inited", 1, ob);
                if ( mapp(map_status = ob->query_skill_map()) ) {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        if (sscanf( perform_actions[j], "%s.c", perform_actions[j] )==1)
                                        {
                                                if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                                else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                                combat_actions += msg;
                                        }
                                }
                        }
                }
                set( "chat_chance_combat", 60);                
                set( "chat_msg_combat", combat_actions );                
        return 1;
}
void dest_me(object ob)
{
        message_vision("只見$N忽然急轉身行，縱身鑽進行人中，轉眼就蹤跡皆無。\n",ob);
        destruct(ob);
}