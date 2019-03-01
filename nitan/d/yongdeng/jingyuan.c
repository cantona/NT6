// Room: /huanghe/jingyuan.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "靖遠");
        set("long", @LONG
靖遠是個不大不小的城鎮，黃沙在離城四十裡的地方被一排排的鑽天
白楊樹給擋住了。因此這裡有了一塊較大的綠洲，聚集了不少從別處來的
移民。這些白楊據說是當年唐朝李靖趕走了突厥後在這裡屯兵時所種。這
也是靖遠得名的由來。西邊不遠就是黃河，南面是一大片沙漠。
LONG );
        set("exits", ([
                "north"     : __DIR__"hongshanxia",
                "south"     : __DIR__"shamo",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}