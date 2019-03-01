// senlin1.c

inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "百木園");
        set("long", @LONG
這裡是梅莊的百木園，你一走到這裡，就象走到了一個連綿無盡
的小森林一樣，這裡無數的鬆樹，柏樹，白楊，還有很多叫不出來名
字的異種苗木。
LONG );
        set("exits", ([
            "south" : __DIR__"keting",
            "north" : __DIR__"neiyuan",
            "east" : __DIR__"senlin2",
            "west" : __DIR__"neitang",
        ]));

        set("outdoors", "meizhuang");
        setup();
        replace_program(ROOM);
}
