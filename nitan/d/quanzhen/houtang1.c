// houtang1.c 後堂一進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後堂一進");
        set("long", @LONG
這裡是後堂的一進，是平常全真教弟子休息的地方。由于全真教
現在廣收弟子，堂中擺放的桌椅也不斷增加，顯得這個堂已經很擁擠
了。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"houtang2",
                "west" : __DIR__"laojundian",
        ]));

        set("coor/x", -2760);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}