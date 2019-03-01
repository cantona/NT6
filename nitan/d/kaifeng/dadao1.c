inherit ROOM;

void create()
{
          set ("short", "三叉路口");
        set("long", @LONG
道路至此分為三路，一條路向北就是開封城，東南面是座樹林。
林中隱有條小道穿過。西南面的路通向野豬林。
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "southwest" : __DIR__"dadao2",
                  "southeast" : __DIR__"shulin",
                  "north" : __DIR__"dadao",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2110);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}