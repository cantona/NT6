inherit ROOM;

void create ()
{
        set ("short", "山路");
        set("long", @LONG
這是一條黃土飛揚的山路，因為離嵩山等幾處山脈還比較遠，所
以它很是寬闊，路上來往人很多，路邊相隔不遠就有個小亭子供行人
歇腳，北邊不遠便是嵩山入口。
LONG );

        set("outdoors", "kaifeng");
        set("exits", ([
                "north" : "/d/songshan/taishique",
                "east" : "/d/shaolin/maowu",
                "eastup" : __DIR__"shanlu1",
        ]));

	set("coor/x", -5080);
	set("coor/y", 2270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}