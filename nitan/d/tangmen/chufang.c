//chufang.c                四川唐門─廚房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long",
"這裡是蓮藕小築中的廚房。屋子中擺著七、八張桌子，一些唐門弟子\n"
"圍坐在桌旁一邊開懷暢飲，一邊談論著江湖上的一些恩恩怨怨，你應該可\n"
"以向廚師點菜(serve)。\n"
);
        set("exits", ([
                        "east" : __DIR__"chaifang",
        ]));
        set("no_fight", 1);
        set("area", "tangmen");
        setup();
}
void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
        object ob, food, water;
        ob = this_player();
        food=new(__DIR__"obj/jiangnr");
        water=new(__DIR__"obj/donggt");

         if( (present("rou", ob)) && (present("tang", ob)) )
        {
                message_vision(HIC "\n廚師沖著你大叫著：“先吃完了再要。\n" NOR, ob);
                return 1;
        }
        else
        {
                if ( (present("rou", ob)) )
                {
                        message_vision(HIC "\n廚師將一碗冬瓜湯放在$N面前，嘴裡嘟囔著：“有吃的還要！”。\n" NOR, ob);
                        water->move(ob);
                        return 1;
                };
                if ( (present("tang", ob)) )
                {
                        message_vision(HIC "\n廚師將一盤醬牛肉放在$N面前，嘴裡嘟囔著：“有喝的還要！”。\n" NOR, ob);
                        food->move(ob);
                        return 1;
                }
                else
                {
                        message_vision(HIC "\n廚師將一盤醬牛肉、一碗冬瓜湯放在$N面前。\n" NOR, ob);
                        food->move(ob);
                        water->move(ob);
                        return 1;
                }

        }
}