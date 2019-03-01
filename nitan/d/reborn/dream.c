#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "【夢境】" NOR);
        set("long", CYN @LONG
這裡是夢境。你感覺到迷迷糊糊的，意識很不清晰。
四處都是白茫茫一片，看什麼都不真切。
LONG NOR );
 /*       set("exits", ([
                "enter" : __DIR__"sky1",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_magic", 1);
        set("objects", ([
                "/adm/npc/buddha2": 1,
        ]));

        setup();
}

void init()
{    
    object me = this_player();
    if ( !userp(me) ) return;

    add_action("do_wake", "wake");
    set_temp("apply/name", ({"夢遊者"}), me);
    set_temp("apply/short", ({"夢遊者(dreamwalker)"}), me);
    set_temp("apply/long", ({"夢遊者(dreamwalker)\n"}), me);
}

int do_wake()
{
   object room, me = this_player();

   message_vision("$N忽然輕飄飄地飛了起來，一下就飛走了。\n", me);
  
   delete_temp("apply/name", me);
   delete_temp("apply/short", me);
   delete_temp("apply/long", me);
   if( query_temp("dream_place", me) )
   {     
      me->move(query_temp("dream_place", me));
      delete_temp("dream_place", me);
   } else
   me->move("/d/city/kedian");
   message_vision("$N揉揉惺忪的睡眼，清醒了過來。\n", me); 
  return 1;
}