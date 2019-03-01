inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "山麓");
        set("long", @LONG
這裡是襄陽城外的山麓，也是南下蒙古軍隊的必經之路，道路曲
折盤旋，十分難走，但是對于出征的大軍來說，走這樣難走的路都好
象已經成了極平常的事了。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "west"  : __DIR__"syuanmen1",
                "east"  : __DIR__"conglin3",
        ]));

        setup();
} 
