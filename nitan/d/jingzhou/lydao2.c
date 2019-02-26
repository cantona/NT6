inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
這是一條安靜的林蔭道，地上鋪着奇奇怪怪五顏六色的石子，向
南北兩頭延伸。西面是高大的荊州城牆。南邊好像有一眼温泉。
LONG );
        set("outdoors", "jingzhou");
        set("objects", ([
                  "/d/kaifeng/npc/qigai" : 1,
        ]));        
        set("exits", ([
                "north" : __DIR__"lydao1",
                "southdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7130);
	set("coor/y", -2060);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}