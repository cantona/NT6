inherit ROOM;

void create()
{
        set("short", "接引佛殿");
        set("long", @LONG
接引佛殿向來是開封城內最熱鬧的地方。誰不想被接引到西方佛
地呢。殿內供奉接引佛像，佛像前供桌上一盞佛門心燈造形奇古，整
日長明，從此殿出去，就能看到開封鐵塔了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"road6",
                  "east" : __DIR__"tieta",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}