inherit ROOM;

void create ()
{
        set ("short", "山路");
        set("long", @LONG
這是一條黃土飛揚的山路，因為離嵩山等幾處山脈還比較遠，所
以它很是寬闊，路上來往人很多，路邊相隔不遠就有個小亭子供行人
歇腳，向南去不遠就是開封城。由北而上直通嵩山，由此前住嵩山進
香、遊玩的客人絡繹不絕。
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "eastdown" : __DIR__"jiaowai",
                  "westdown" : __DIR__"shanlu2",
        ]));

	set("coor/x", -5070);
	set("coor/y", 2270);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}