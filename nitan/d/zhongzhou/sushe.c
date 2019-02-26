inherit ROOM;

void create()
{
        set("short", "演員房間");
        set("long", @LONG
這裏是是戲院內演員的休息的地方，好幾張大牀佔了房間
的大半，牀上男的女的衣服亂七八糟，看起來他們男的女的就
混在一起睡。北面的牆上有幾張名角的畫像。
LONG);

        set("exits", ([
                "south" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/kid1" : 2,
        ]));

        set("coor/x", -9050);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}