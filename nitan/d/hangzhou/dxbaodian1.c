// dxbaodian1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大雄寶殿");
        set("long", @LONG
天王殿後是另一座高達三十幾米的大殿。匾上寫着“大雄寶殿”。
殿前有兩座八角九層石塔。往南又進了天王殿。
LONG);
        set("exits", ([
                "south"     : __DIR__"tianwangdian",
                "enter"     : __DIR__"dxbaodian2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 739);
	set("coor/y", -2041);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}