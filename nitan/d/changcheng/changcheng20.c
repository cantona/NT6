// Room: /d/changcheng/changcheng20.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
由於長期受到風沙的侵蝕，不少城牆已經倒塌。牆角的黃沙中有許
多從城牆上掉下來的青磚。抬眼望去，只見城牆外是一望無邊的黃沙，
周圍安靜極了，向一片死亡的世界，偶爾天上飛過一隻蒼鷹。遠遠的可
以看見西邊有一座關卡。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "west"      :__DIR__"changcheng21",
                "northeast" :__DIR__"changcheng19",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -16000);
        set("coor/y", 9000);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}