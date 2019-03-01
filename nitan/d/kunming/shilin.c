inherit ROOM;

void create()
{
        set("short", "石林");
        set("long", @LONG
這裡矗立著各種各樣形狀各異的石頭，有的象人，有的象
樹，有的又象動物，你這邊看著象這樣，也許換個角度又象其
他的，千姿百態。把你眼睛都看花了。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "north" : __DIR__"xiaolu", 
                "south"  :__DIR__"shilin1",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}