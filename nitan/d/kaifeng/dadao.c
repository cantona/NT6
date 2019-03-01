inherit ROOM;

void create()
{
          set ("short", "大道");
        set("long", @LONG
在平原之上的一條大路，來往人很多，路邊相隔不遠就有個小亭
子供行人歇腳，向北去就是開封城。南面不遠是個三叉路口。
LONG );
          set("outdoors", "kaifeng");

          set("exits", ([
                  "south" : __DIR__"dadao1",
                  "north" : __DIR__"nanying",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2120);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}