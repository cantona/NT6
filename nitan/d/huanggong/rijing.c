// Room: /d/huanggong/rijing.c

inherit ROOM;

void create()
{
        set("short", "日精門");
        set("long", @LONG
日精門北邊是南書房, 南邊是祭孔處, 這裏是皇帝經常出行坐轎的
地方.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"qianqingmen",
                "east" : __DIR__"yuqinggong",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2800);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}