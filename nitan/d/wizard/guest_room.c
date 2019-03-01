#include <ansi.h>
#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIY "巫師會客室" NOR);
        set("long", @LONG
這裡是巫師和玩家交流的地方，如果你有什麼問題需要向巫師請
教，可以在這裡留言(post)。不過如果問題牽涉到解謎或者已經在幫
助文件裡有詳細說明，巫師們就不一定會回答。樓上是巫師休息室，
一般玩家到這裡後就上不去了
LONG );

        set("exits", ([
                "up"        : __DIR__"wizard_room",
                "north"     : __DIR__"noname_room",
                "south"     : __DIR__"develop_room",
                "southeast" : "/d/city/wumiao",
        ]));

        set("no_fight", 1);
        create_door("southeast", "竹門", "northwest", DOOR_CLOSED);
        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 9990);
        setup();
        "/clone/board/towiz_b"->foo();
}


int valid_leave(object me, string dir)
{
        if (dir == "up" && (! userp(me) || ! wizardp(me)))
                return notify_fail("那裡只有巫師才能進去。\n");
        return ::valid_leave(me, dir);
}