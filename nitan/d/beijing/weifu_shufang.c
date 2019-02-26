#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韋府書房");
        set("long", @LONG
這裏是韋公爺的書房，房間寬敞明亮，正對着門是一大紅木書桌，
書桌旁一個六尺高的黃銅香爐，四周的書架上堆放滿了各種書籍，不
過很容易看出已經很就沒人動過了。
LONG );

        set("exits", ([
                "south" : "/d/beijing/weifu_dating",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
}