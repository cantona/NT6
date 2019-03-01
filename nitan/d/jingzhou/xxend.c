inherit ROOM;

void create()
{
        set("short", "小巷盡頭");
        set("long", @LONG
這是一條又深又黑的巷子，散發出一陣陣污水的味道和食物發霉
的味道，又臟又臭。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "north" : __DIR__"xxiang",
                "south" : __DIR__"yuanmiaoguan",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/qigai" : 2,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}