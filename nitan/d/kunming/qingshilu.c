inherit ROOM;

void create()
{
        set("short", "青石路");
        set("long", @LONG
出了石林，就到了昆明的官道，青石鋪成，平坦寬闊，西
去不遠就是昆明瞭。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"qingshilu1", 
                "east" : __DIR__"shilin2",
        ]));
	set("coor/x", -16790);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}