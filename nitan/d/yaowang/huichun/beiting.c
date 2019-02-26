#include <room.h>
inherit ROOM;

void create()
{
        set("short", "北廳");
        set("long", @LONG
這裏是回春堂的帳房，帳房先生正坐在門邊的一張桌子後面。由於
回春堂生意興隆，藥王谷的弟子已經忙不過來，所以大量僱傭零工夥計，
工錢不低的。如果手頭缺錢或是想學習醫藥學，不妨在這裏打打工。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "west" : __DIR__"xiuxi",
                "south" : __DIR__"tingyuan",
        ]));
        set("objects", ([
                __DIR__"npc/zhangfang" : 1,
        ]));
        create_door("west", "木門", "east", DOOR_CLOSED);
        setup();
}
