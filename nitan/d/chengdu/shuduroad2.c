// Room: shuduroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "蜀都大道");
        set("long", @LONG
這裡是蜀都大道，它橫貫整個錦官城。向東就可以到提督府了。
平頭百姓少了，路上大多是有頭有臉的爺們。幾個官兵頂盔貫甲打量
著過往行人。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "west"  : __DIR__"westroad2",
            "east"  : __DIR__"guangchang",
        ]));
        set("objects", ([
            "/d/city/npc/bing" : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15230);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}