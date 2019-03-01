inherit ROOM;

void create()
{
        set("short", "大校場");
        set("long", @LONG
這裡是用來校閱軍士的地方。只見校場正中巍巍搭著一座高台，台南
排列著千余張椅子板凳。台前豎著兩根旗桿，旗桿頂上還有著碩大的旗鬥。
校場裡聚集著數百名官兵和武將，看來這裡將要進行閱兵式。
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