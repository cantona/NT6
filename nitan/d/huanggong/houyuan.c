// houyuan.c
inherit ROOM;

void create()
{
        set("short", "清和殿後院");
        set("long", @LONG
這裡是清和殿後院。院裡種著些青菜。牆角有一口水井(well)。站
在水井邊往下看，只覺深不見底，井壁上滿是滑溜溜的青苔。一個□轆
吊著一根長繩，繩端系著一個木桶。北邊是一條走廊，通往御膳房。
LONG
        );
        set("outdoors", "huanggong");
        set("resource/water", 1);
        set("exits", ([
                "north" : __DIR__"yushanfang",
        ]));
        set("item_desc", ([
                "well" : "一口枯井，相傳跳進去可以美容。\n"
        ]));

	set("coor/x", -2790);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}