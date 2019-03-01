inherit ROOM;

void create()
{
        set("short", "英雄樓");
        set("long", @LONG
英雄酒樓裡桌椅潔凈。座中客人衣飾豪奢，十九是富商大賈。這
裡可以俯瞰佛山鎮全景。
LONG );
        set("objects", ([
                __DIR__"npc/pang": 1,
                __DIR__"npc/shou": 1,
        ]));
        set("exits", ([
                "down" : __DIR__"yingxionglou",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9760);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}