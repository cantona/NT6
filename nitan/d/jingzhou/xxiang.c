inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
這是一條又深又黑的巷子，散發出一陣陣污水的味道和食物發黴
的味道，又髒又臭。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "south" : __DIR__"xxend",
                "north" : __DIR__"dongdajie2",
        ]));

        set("coor/x", -7080);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}