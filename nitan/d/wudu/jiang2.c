#include <ansi.h>
inherit RIVER;

void create()
{
        set ("short", "桃花江東岸");
        set ("long", @LONG
這裡是桃花江 (river)邊，江水清澈，水流平緩，兩岸都
是無邊的桃樹，不斷有桃花隨風飄入江中，隨波逐流。江邊停
泊著一條渡船。
LONG);
        set("to", "/d/wudu/jiang1");
        set("exits", ([
                "east" : __DIR__"cun1",
                "south" : __DIR__"xiao1",
        ]));

        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "wudujiao");
        setup();
        replace_program(RIVER); 
}
