inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這是一條寬闊的青石板街道，南邊是一座簡樸的院子，半月形的
大門上方寫著『蕭湘書院』四個燙金的大字，蒼勁挺拔有力。裡面不
時地傳來學生們抑揚頓挫的讀書聲。北邊是一座幾層高的白塔，相傳
是一位狀元為報母養育之恩而建造的。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"dongdajie2",
                "south" : __DIR__"shuyuan",
                "west" : __DIR__"guangchang",
                "north" : __DIR__"baita",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 2,
        ]));
        set("coor/x", -7090);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}