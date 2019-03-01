// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>

inherit ROOM;
void create()
{
       set("short","海船");
       set("long", @LONG
這是遼闊的海面，海風「呼呼」在你耳邊吹過，海浪一個接著一個向
你潑打過來，突然一個巨浪打來幾乎把你所乘的船掀翻。你快要陷入這個
旋渦中了，還是催促漁夫趕緊搖船走出著鬼地方吧。
LONG );


//        set("exits", ([
//                "east" : __FILE__,
//                "west" : __DIR__"dahai2",
//                "south" : __DIR__"dahai3",
//                "north" : __DIR__"dahai4",
//        ]));
        setup();

}

/*
int valid_leave(object me, string dir)
{
        if ( dir == "west")
            addn_temp("mark/steps", 1, me);
        if ( dir == "east")
            addn_temp("mark/steps", -1, me);
        if ( dir == "north")
            addn_temp("mark/nsteps", 1, me);

        if( query_temp("mark/steps", me) == 10 )
         {
            me->move("/d/shenlong/tanggukou");
            delete_temp("mark/steps", me);
             return notify_fail("終于你看見了前方的陸地，啊，謝天謝地 ！\n");
         }

     if( query_temp("mark/steps", me) == -10 )
            {
               me->move("/d/shenlong/haian");
           delete_temp("mark/steps", me);
             return notify_fail("終于你看見了前方的陸地，啊，謝天謝地 ！\n");
        }

      if( query_temp("mark/nsteps", me) == 10 )
         {
            me->move("/d/shenlong/lushunkou");
            delete_temp("mark/nsteps", me);
             return notify_fail("終于你看見了前方的陸地，啊，謝天謝地 ！\n");
         }


        return ::valid_leave(me,dir);
}

void init()
{
        object me = this_player();

        if( interactive(me = this_player()) )
        {
            remove_call_out("arrive");
            call_out("arrive", 10);
        }

}

void arrive()
{
        message("vision", "漁夫說：“大陸到啦，上岸吧”。\n",this_player());
        this_player()->move("/d/shenlong/tanggu");
}
*/

int valid_leave(object me, string dir)
{
        object room;

        if ( !::valid_leave(me, dir) )
                return 0;

        if(!(room = find_object(__FILE__)) )
                room = load_object(__FILE__);
        if(objectp(room))
        {
                addn_temp("person_inside", -1, room);
                if( room->addn_temp("person_inside",-1) <= 0 )
                        delete_temp("person_inside", room);
        }

        return 1;
}
