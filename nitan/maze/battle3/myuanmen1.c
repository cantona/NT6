#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "轅門外"NOR);
        set("long", @LONG
這裏就是「蒙古」軍營駐紮地了，遠遠地可以看見大營內飛揚的
塵土，不時有幾匹快馬飛奔進出，你正欲再看，忽然嗖地一枚冷箭從
你頭上飛過，還是趕快離開的好。
LONG );
        set("defence",120);
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south"  : __DIR__"caoyuan4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
}

void init()
{
        object me = this_player();

        if( query_temp("warquest/party", me) == "song" )
                add_action("do_break", "break");
}

int do_break()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if( query("exits/north", room) )
                return notify_fail("轅門的的防禦已經被擊破了，快衝進去啊！\n");

        if( query("defence", room)<1 )
        {
                set("defence", 0, room);
                tell_object(me, HIR "轅門的的防禦已經被擊破了，快衝進去啊！\n" NOR);
                set("exits/north", __DIR__"mying", room);
                call_out("door_close", 20, room);
                return 1;
        } else
        {
                if( query_temp("warquest/group", me) < 1 )
                        return notify_fail("你還是帶領隊伍來攻擊轅門的防禦工事吧！\n");

                message_vision(
                        HIY "$N帶着一支攻城隊伍正加緊攻擊着轅門的防禦工事！\n" NOR, me);
                addn("defence", -random(query_temp("warquest/group", me)), room);
                me->start_busy(3 + random(2));
                return 1;
        }
}

void door_close(object room)
{
        if( query("exits/north", room) )
        {
                delete("exits/north", room);
                tell_object(all_inventory(room),
                        HIW "蒙古軍連忙帶着一支隊伍把轅門的防禦工事修好了！\n" NOR);
        }
        return;
}

