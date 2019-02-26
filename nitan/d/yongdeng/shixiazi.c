// Room: /huanghe/shixiazi.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "石峽子");
        set("long", @LONG
石峽子是以前的黃河故道，現在遍地是大大小小的鵝卵石，兩邊
是數丈高的高坡，千溝萬壑，向你訴説着世事的滄桑。要是運氣好的話
你可以在這裏揀到非常漂亮、非常珍貴的雨花石。
LONG );
        set("exits", ([
                "southwest" : __DIR__"tumenzi",
                "northeast" : __DIR__"bingcao",
        ]));
        set("objects", ([
                "/d/city/obj/shitou" : 1,
                "/d/hangzhou/obj/eluanshi" :1,
        ]));
        set("outdoors", "yongdeng");
        set("coor/x", -16100);
	set("coor/y", 4260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}