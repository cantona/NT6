inherit ROOM;

void create()
{
        set("short", "漕幫裏屋");
        set("long", @LONG
這裏是漕幫的裏屋，幾個流氓惡霸正在賭錢。邊上有個小
門，是漕幫為了有事發生的時候的緊急通道。
LONG);
        set("exits", ([
                "out" : __DIR__"eba",
                "south" : __DIR__"hutong2",     
        ]));

        set("coor/x", -9010);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}