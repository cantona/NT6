// liangong.c 練功房
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裡是全真教弟子練功的房間。這座房間形狀甚是奇特，前窄
後寬，成為梯形，東邊半圓，西邊卻作三角形狀，原來這是全真教
獨有的練功室，前窄練掌，後寬使指，東圓研劍，西角發鏢。房間
中央立著幾個練功用的木人，吊著幾個沙袋(bag)和紙冊(paper)。
LONG );

        set("exits", ([
                "south" : __DIR__"houtang2",
                "north" : __DIR__"chanfang2",
        ]));
        set("item_desc", ([
                "paper" : "這是一摞厚厚的牛皮紙冊，用鐵釘釘在牆上。好象可以
用來練掌法的，打打(da paper)試試看。\n",
                "bag"   : "這是一個大沙袋，看起來非常結實。好象是用來練指法
的，你可以打打(ci bag)看。\n",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("coor/x", -2740);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
}
void init()
{
      add_action("do_strike", "da");
      add_action("do_finger", "ci");
}

int do_finger()
{
      object me;
      int qi_cost,c_exp,c_skill;
      me = this_player();
      c_exp=query("combat_exp", me);
      c_skill=me->query_skill("finger",1);
      qi_cost = 10;
      if( query("qi", me)>qi_cost )
      {
           message_vision( "$N伸指狠狠地點向沙袋，覺得指尖微微有些痛。\n", me );
           if (((c_skill*c_skill*c_skill/10)< c_exp) && (c_skill<101))
           me->improve_skill("finger", (int)me->query_skill("finger", 1));
           me->receive_damage("qi", qi_cost );
      }
      else
           me->unconcious();        
      return 1;
}

int do_strike()
{
      object me;
      int qi_cost,c_exp,c_skill;
      me = this_player();
      c_exp=query("combat_exp", me);
      c_skill=me->query_skill("strike",1);
      qi_cost = 10;
      if( query("qi", me)>qi_cost )
      {
           message_vision( "$N蹲了一個馬步，揮掌擊向牛皮紙冊。\n", me );
           if (((c_skill*c_skill*c_skill/10)< c_exp) && (c_skill<101))
           me->improve_skill("strike", (int)me->query_skill("strike", 1));
           me->receive_damage("qi", qi_cost );
      }
      else
           me->unconcious();
      return 1;
}