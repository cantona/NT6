// Room: /d/kunlun/xuedi.c
// Last Modified by winder on Jun. 29 2001
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "雪地");
        set("long", @LONG
雪地中央有個大雪堆，這大雪堆是農家積柴的草堆。這天寒地凍的
隆冬嚴寒裡，屍體不會腐臭，天上有一頭兀鷹在空中盤旋了幾個圈子，
尋找機會以便飛下來啄食。
LONG );
        set("outdoors", "hongmei");
        set("exits", ([
                "south" : __DIR__"kekexili",
        ]));
        set("objects", ([
                "/clone/misc/corpse" : 1,
        ]));
        set("coor/x", -100000);
        set("coor/y", 20010);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}