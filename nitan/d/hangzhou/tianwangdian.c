// tianwangdian.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "天王殿");
        set("long", @LONG
走進大殿，只見正面坐着袒胸露腹的弭勒佛，兩旁是四大天王，
後面是神態威嚴的韋馱菩薩。天王殿後面便是大雄寶殿。
LONG);
        set("exits", ([
                "out"       : __DIR__"lingyinsi",
                "north"     : __DIR__"dxbaodian1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 739);
	set("coor/y", -2051);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}