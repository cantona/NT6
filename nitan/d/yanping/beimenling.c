// Room: /d/yanping/beimenling.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "北門嶺");
        set("long", @LONG
延平府北城牆建與山崖絕壁之間，蜿蜒起伏於北門嶺間。背後就是
高達天際的茫蕩山了，從此西下進入溪源十里畫廊，直達茫蕩深處的溪
源。
LONG );
        set("exits", ([
                "northwest" : __DIR__"youlang",
                "southdown" : __DIR__"meishanpo",
        ]));
        set("outdoors", "jiangnan");
        set("no_clean_up", 0);
        set("coor/x", 1480);
        set("coor/y", -6160);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}