// Room: /d/huanggong/yuehua.c

inherit ROOM;

void create()
{
        set("short", "月華門");
        set("long", @LONG
月華門北邊是批本處, 南邊是奏事房, 這裏是皇帝經常出行坐轎的
地方.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"qianqingmen",
                "west" : __DIR__"yangxin",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2820);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}