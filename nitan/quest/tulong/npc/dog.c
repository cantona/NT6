//dog.c
#include <ansi.h>
#include <command.h>

inherit NPC;

void create()
{
      set_name("小狗", ({ "dog" }) );
      set("title", "可愛的小東西");
      set("race", "野獸");
      set("gender", "雄性" );
      set("age", 10);
      set("str", 22);
      set("int", 30);
      set("cps", 30);
      set("con", 30);

      set("long", "你看到的是一隻長毛的小狗。\n");
      set("combat_exp", 2000000);
      set("attitude", "friendly");

      set("max_qi", 10000);
      set("max_jing", 10000);
      set("inquiry", ([
      ]) );
      setup();
}

void init()
{
      object ob;

      ::init();
      add_action("do_pat","pai");
      add_action("do_wei","wei");

      if ( interactive(ob = this_player()) && !is_fighting() )
      {
             remove_call_out("wangwang");
             call_out("wangwang", 1, ob);
      }
}

void wangwang(object ob)
{
      if( query("id", ob) == "night" )
            message_vision("小狗高興地衝你直搖尾巴。\n",ob);
      else
            message_vision("小狗不高興地地衝你汪汪兩聲。\n",ob);
}

int do_pat(string arg)
{
      set("chanxin/save", 1, this_player());
      message_vision("小狗高興地衝你搖了兩下尾巴。\n",this_player());
      return 1;
}

int do_wei(string arg)
{
      if( query("chanxin/save", this_player()) >= 1 )
      {
            set("chanxin/save", 2, this_player());
            message_vision("小狗高興地衝你搖了兩下尾巴。\n",this_player());
            return 1;
      }
      else
      {
            message_vision("小狗高興地衝你搖了兩下尾巴。\n",this_player());
            return 1;
      }
}
