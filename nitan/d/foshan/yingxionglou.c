inherit ROOM;

void create()
{
        set("short", "英雄樓");
        set("long", @LONG
英雄樓乃是佛山大豪「南霸天」鳳天南的家業。酒樓裏桌椅潔淨。
座中客人衣飾豪奢，十九是富商大賈。佛山地處交通要地，來這吃飯
的人還真不少。
LONG );
        set("objects", ([
                __DIR__"npc/fengqi": 1,
        ]));
        set("exits", ([
                "north" : __DIR__"street4",
                "south" : __DIR__"majiu",
                "up"    : __DIR__"yingxionglou2",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}