#include <room.h>
inherit ROOM;

void create()
{
        set("short", "匯英酒樓");
        set("long", @LONG
匯英酒樓在整個京城中，也算是小有名氣的了。酒樓裡面雕樑畫
壁，裝飾有如宮殿，你可以在這裡打聽到各地的風土人情。店小二裡
裡外外忙得不可開交，接待著南腔北調的客人。樓裡桌椅潔凈。座中
客人衣飾豪奢，十九是富商大賈。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yong_1",
                "up" : "/d/beijing/huiyingup",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiaoer2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}