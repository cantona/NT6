// Room: /t/wanjiegu/backyard.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
後院是一大片開闊的草地，綠草如蔭，幾朵野花點綴其間，草地
中間放着一塊大石刻成的棋盤，一個黃眉老僧和一個青袍客正在下棋。
北邊有一間石屋，門口被一塊大石頭(rock)擋住了。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([
            "south" : __DIR__"hall",
        ]));
        set("objects", ([
            __DIR__"npc/monk" : 1,
            CLASS_D("duan") + "/duanyq" : 1,
        ]));
        set("item_desc", ([
            "rock"   : "一塊很大的石頭，擋住了石屋的入口。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_push","push");
}

void check_trigger()
{
        object room;
        if ((int)query("trigger") == 9 &&
            !query("exits/north"))
        {
                message("vision", HIW "大石終於被推開了，露出通向石屋的通道。\n" NOR,
                        this_object());
                set("exits/north", __DIR__"stone_room");
                delete("trigger");
        }
}

int do_push(string arg)
{
        string dir;
        object me = this_player();

        if (me->is_busy())
        {
             message_vision("你的上一個動作還沒有完成！\n", me);
             return 1;
        }

        if (!arg || arg=="")
        {
             write("你要幹什麼？\n");
             return 1;
        }

        if (arg == "rock")
        {
                if ( me->query_str() < 25 )
                {
                        tell_object(me,"你的力氣太小了，用點內力試試看！\n");
                        return 1;
                }
                me->start_busy(2);
                message_vision(HIW "$N氣運丹田，發內力推動大石頭。\n" NOR,me);
                call_out("pushstone", 2, me);
                me->stop_busy();
                check_trigger();
                return 1;
        }
}

int pushstone(object me)
{
        if( query("neili", me) >= query("neili_factor", me) )
        {
                message_vision(HIW "大石頭動了一下。\n" NOR, me);
                addn("neili", -query("neili_factor", me), me);
                addn("trigger", 1);
                return 1;
        } else
        {
                tell_object(me, "你的內力不夠了，休息一會再推吧！\n");
                return 1;
        }
}

void reset()
{
        ::reset();
        delete("trigger");
        delete("exits/north");
}