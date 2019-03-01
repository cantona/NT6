// Room: /d/suzhou/zhenniang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "真娘墓");
        set("long", @LONG
試劍石北面就是古真娘墓，真娘也稱貞娘，因安史之亂流落江南，
受騙流落墮入青樓。貞娘為守貞操，自盡抗之。後人築亭其上，墓前石
刻“香魂”兩字，墓上遍栽花卉。唐代白居易等詩人墨客紛紛為之題詩，
褒讚真娘之貞烈。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"sunwuting",
                "southwest" : __DIR__"shijianshi",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}