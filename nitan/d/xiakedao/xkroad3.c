// Room: /d/xiakedao/xkroad3.c
// Modified by Java on Feb.14.1998
inherit BUILD_ROOM;

void create()
{
        set("short", "平原小路");
        set("long", @LONG
你走在珠江三角洲的平原小路上。此處向稱魚米之鄉，有花果之
都美譽，物產豐饒，民風淳樸。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : "/d/foshan/southgate",
                "south"   : __DIR__"xkroad4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -8000);
        set("coor/z", 0);
        setup();
}
