inherit ROOM; 
#include <ansi.h> 
void init();
int do_move(string arg);
int do_enter(object me);

void create()
{ 
      set("short", "白砂台");
      set("long",
"[1;32m白砂台約有一丈見方，上面有細沙鋪就，整個枱面非常的平\n"
"整。台中央有一塊大石頭(stone)，堵住了泉眼。\n"
);
  set("exits",([
      "east" : __DIR__"spirit4",
  ]));
  set("item_desc", ([
      "stone" : "這塊石頭看起來不算太大，你應該可以搬動(move)它。\n",
  ]));
//  set("no_clean_up", 0);
  set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_enter", "enter");
}

int do_move(string arg)
{      
        object room; 
        object me=this_player();
        if(!arg || arg!="stone")
          return notify_fail("你要移動什麼？\n");
        if((int)me->query_str()>25)
                {
message_vision(HIC"$N用力推開大石頭，泉水又開始流了出來！似乎可以潛下去(enter)。\n"NOR,this_player() ); 
message_vision(HIC"一隻小精靈出現在$N面前，説：謝謝你解開第二個封印，請你繼續前進吧。\n"NOR,this_player() ); 
                set_temp("m_success/初級", 1, this_player());
                set("move_stone",1);
        if(!( room = find_object(__DIR__"entrance")) )
                room = load_object(__DIR__"entrance");
        if(objectp(room)) 
            {
                set("exits/down", __DIR__"spirit3", room);
                message("vision","泉眼中又湧出了泉水。\n",room);
            }                }
        else
                message_vision("$N使出吃奶的力氣也挪不動石頭，只好悻悻地放棄了。\n", this_player());    
        return 1;       
}

int do_enter(object me)
{
        object room;
        object where;
        me=this_player();
        where=environment(me); 
       if( !query("move_stone", where) )
          return notify_fail("你要進哪去？\n");        if(!( room = find_object(__DIR__"spirit5")) )
          room = load_object(__DIR__"spirit5");
        message_vision("$N“咕咚”一聲，跳進泉水中。\n",me); 
        set("move_stone",0);        me->move(room);
        return 1;
}

