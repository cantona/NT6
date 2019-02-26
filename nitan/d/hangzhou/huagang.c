// huagang.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "花港觀魚");
        set("long", @LONG
只見湖中有一小島，一座曲橋橫跨湖面。曲橋上人羣熙攘，倚欄
投餌。橋下紅魚，爭食歡跳。謝覺哉遊園時曾作詩一首“魚國羣粼樂
有餘，觀魚才覺我非魚。虞詐兩忘欣共處，魚猶如此況人乎。”
LONG);
        set("exits", ([
            "east"     : __DIR__"suti6",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/baizhi" : random(2),
        ]));
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}