#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
一個雜草叢生的四合院院子，大院北邊是一條黑漆漆的胡同，四
周是幾間房屋，房屋也不怎麼破舊。院中橫七豎八的倒著一些石鎖、
鐵環等尋常百姓健身用的器材。一個道人站在大院的正中，虎視耽耽
的盯著你。
LONG );
       set("exits", ([
                "north" : "/d/beijing/qingmu_men",
                "south" : "/d/beijing/qingmu_fang2",
                "east" : "/d/beijing/qingmu_fang1",
                "west" : "/d/beijing/qingmu_fang3",
        ]));
        set("objects", ([
                CLASS_D("yunlong") + "/xuanzhen" : 1
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}