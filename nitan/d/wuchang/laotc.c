//Edited by fandog, 02/15/2000

inherit ROOM;

void create()
{
        set("short", "老通城");
        set("long", @LONG
你一走進來，就聞到一股煎豆皮的香味。這是武漢最有名的小吃店，
喜歡吃豆皮、凍豆腐的客人們散坐各處，一位嬌憨可人的年輕女人在忙
乎著。雖說有點鬧哄哄的，但閒坐于此，聽聽江湖掌故，嚼嚼香酥可口
的豆皮，也是一大樂事。
LONG );
        set("resource/water", 1);
        set("exits", ([
                "east" : __DIR__"hzjie2",
        ]));
        set("objects", ([
                __DIR__"npc/woman" : 1,
        ]));
	set("coor/x", -5100);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}