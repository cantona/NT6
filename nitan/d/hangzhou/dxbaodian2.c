// dxbaodian2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大雄寶殿");
        set("long", @LONG
殿內正中一尊如來佛像，兩旁塑有二十尊諸天的佛像，大殿後壁
有五十三參海島像，島上有姿態各異的大小佛像一百五十個。
LONG);
        set("exits", ([
                "out"     : __DIR__"dxbaodian1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 738);
	set("coor/y", -2042);
	set("coor/z", -2);
	setup();
        replace_program(ROOM);
}