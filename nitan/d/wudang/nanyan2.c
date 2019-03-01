#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        object ob1, ob2;
        set("short", "南巖迷宮");
        set("long", @LONG
你現在南巖宮地下密室中，高掛的腕粗的油燭照得滿堂透亮。但
周圍靜謐如夜，除了燭火閃爍的風聲外，你什麼也聽不見。這裡只有
你一個人。你腳下緩緩而動，全神戒備，沒有人能幫助你。
LONG );
        set("exits", ([
                "east"      : __DIR__"nanyan1",
                "south"     : __DIR__"nanyan2",
                "west"      : __DIR__"nanyan3",
                "north"     : __DIR__"nanyan4",
                "southeast" : __DIR__"nanyan1",
                "southwest" : __DIR__"nanyan0",
                "northeast" : __DIR__"nanyan3",
                "northwest" : __DIR__"nanyan4",
        ]));
        set("objects", ([
                __DIR__"obj/table" : 1,
                "/clone/misc/corpse" : 1,
        ]) );
        setup();
        replace_program(ROOM);
}