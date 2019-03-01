// yushanang.c
inherit ROOM;

void create()
{
        set("short", "御膳房");
        set("long", @LONG
遠遠就能聞到一陣陣香味從這兒飄出. 這裡是御膳房. 閒雜人等不
能在此出入. 一張張長桌上擺著天下美味, 無不令人垂涎三尺. 可這是
皇上吃的, 你想也甭想.
LONG
        );

        set("exits", ([
                "north" : __DIR__"jianting",
                "south" : __DIR__"houyuan",
                "west"  : __DIR__"qinghedian",
        ]));
        set("objects", ([
                __DIR__"npc/taijian":1,
                __DIR__"obj/yuchi" : 2,
        ]));

	set("coor/x", -2790);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}