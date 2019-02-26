inherit ROOM;

void create()
{
        set("short", "東城門");
        set("long", @LONG
這裏是汝州的東城門。從這裏是通向嵩山去的必經要道，一旦有
大案發生或是戰事起來，立即會在此設卡盤查，平時，官兵也懶得過
來多事。
LONG
        );

        set("exits", ([
                "west" : __DIR__"dongdajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6740);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
