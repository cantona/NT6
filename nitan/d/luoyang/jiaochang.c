inherit ROOM;

void create()
{
        set("short", "大校場");
        set("long", @LONG
這裏是用來校閲軍士的地方。只見校場正中巍巍搭着一座高台，台南
排列着千餘張椅子板凳。台前豎着兩根旗杆，旗杆頂上還有着碩大的旗鬥。
校場裏聚集着數百名官兵和武將，看來這裏將要進行閲兵式。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wroad4",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 2,
                "/d/city/npc/wujiang" : 1,
        ]));
	set("coor/x", -7030);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}