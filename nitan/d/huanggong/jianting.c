// Room: /d/huanggong/jianting.c

inherit ROOM;

void create()
{
        set("short", "紫禁箭亭");
        set("long", @LONG
在一大片空地上有一座箭亭, 又稱紫禁箭亭, 皇上常在這和王公大
臣們一齊射箭, 操練武藝.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 6 */
                "north" : __DIR__"huangjimen",
                "south" : __DIR__"yushanfang",
                "west"  : __DIR__"jingyunmen",
                "east"  : __DIR__"dao3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}