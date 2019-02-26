inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
這裏是客店的二樓幾張大牀一字排開，一些人正在上面睡
的呼嚕震天響，門窗緊閉，官銜昏暗，你不由也想睡山個一覺。
LONG);
        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([
                "eastdown" : __DIR__"kedian",
        ]));
	set("coor/x", -16860);
	set("coor/y", -7230);
	set("coor/z", 10);
	setup();
        
}

int valid_leave(object me, string dir)
{
        if (dir == "eastdown" ) me->delete_temp("rent_paid");

        return ::valid_leave(me, dir);
}