// Room: /huanghe/wufosi.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "五佛寺");
        set("long", @LONG
這裏是一個被廢棄的破廟，周圍全是沙丘，破廟的寺門已經倒塌，地
上有塊半埋在沙裏的匾，從剝落的金字上你依稀可以辨別出“五佛寺”三
個字，唯一尚算完整的建築是大殿，但屋頂上全是窟窿，強勁的西北風吹
過發出難聽的“嗚---嗚---”聲。
LONG );
        set("exits", ([
                "south"     : __DIR__"shimen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -16070);
	set("coor/y", 4280);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}