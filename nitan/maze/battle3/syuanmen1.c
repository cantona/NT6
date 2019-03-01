// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "轅門外"NOR);
        set("long", @LONG
這裡就是「大宋」軍營駐紮地了，遠遠地可以看見一面大旗，上
面書著一個鬥大的隸書「宋」字，再走近些就到軍營了，尋常人還是
不要靠近的好，省得被當成細作捉起來。西邊一個石門通向箭樓，上
面一個鐵門通向城牆。
LONG );
        set("defence",120);
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" : __DIR__"sying",
               "east"  : __DIR__"conglin4",
               "west"  : __DIR__"sying6",
               "up"    : __DIR__"sying5",
        ]));    

        create_door("up", "鐵門", "down", DOOR_CLOSED);
        create_door("west", "石門", "east", DOOR_CLOSED);
        setup();
}
              
void init()
{
        object me = this_player();

        if( query_temp("warquest/party", me) == "meng" )
                add_action("do_break", "break");
        else
        if( query_temp("warquest/party", me) == "song" )
                add_action("do_repair", "repair");
}

int do_repair()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())
                return notify_fail("你正忙著呢！\n");

        if (WAR_D->query_stones(me) < 200)
                return notify_fail("由于缺少足夠的石頭及木材,轅門的防御工事無法修理！\n");

        if( query("defence", room)>999 )
                return notify_fail("轅門的防御工事已經修理好了！\n");
        else
        {
                if( query_temp("warquest/group", me) < 1 )
                        return notify_fail("你還是帶領隊伍來搶修著轅門的防御工事吧！\n");

                message_vision(
                        HIW "$N帶著一支隊伍緊張地搶修著轅門的防御工事！\n" NOR, me);
                addn("defence", random(query_temp("warquest/group", me)), room);
                WAR_D->expend_stones(me, 200);
                me->start_busy(1 + random(2));
                return 1;
        }
}

int do_break()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())        
                return notify_fail("你正忙著呢！\n");

        if( query("defence", room)<1 )
        {
                set("defence", 0, room);
                write("轅門的的防御已經被擊破了，快沖進去啊！\n");
                return 1; 
        } else
        {
                message_vision(
                        HIY "$N帶著一支攻城隊伍正加緊攻擊著轅門的防御工事！\n" NOR,me);
                addn("defence", -random(query_temp("warquest/group", me)), room);
                me->start_busy(2 + random(2));
                return 1;
        }
}

