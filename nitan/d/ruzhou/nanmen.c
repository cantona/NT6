inherit ROOM;

void create()
{
        set("short", "南城門");
        set("long", @LONG
這裡是汝州的南城門。從這裡是通向南陽去的必經要道，一旦有
大案發生或是戰事起來，立即會在此設卡盤查，平時，官兵也懶得過
來多事，城門下一片太平盛世景象。
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaozheng",
                "north" : __DIR__"nandajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
