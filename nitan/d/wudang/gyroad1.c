inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "果園小路");
        set("long", @LONG
眼前豁然開朗，你輕鬆地走在果園邊的小路上。路上落英繽紛，
兩邊是桃樹林，盛開著粉紅的桃花，紅雲一片，望不到邊。還可以看
蜜蜂「嗡嗡」地在花間飛上飛下忙個不停，間或傳來猿猴的嘰咋聲。
LONG );
        set("outdoors", "wudang");

        set("exits", ([
                "west" : __DIR__"tyroad13",
                "east" : __DIR__"gyroad2",
        ]));
        set("objects", ([
                "/clone/beast/mangshe": 1
        ]));
        set("coor/x", -250);
        set("coor/y", -310);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "east" && objectp(present("mang she", environment(me))))
                return notify_fail(HIG "但見巨蟒一個盤身，頓時擋住了你的去路。\n" NOR);

        return ::valid_leave(me, dir);
}
