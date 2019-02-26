// Room: /d/xiangyang/daxiaochang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大校場");
        set("long", @LONG
這是襄陽守軍用來校閲軍士的地方。只見校場正中巍巍搭着一座
高台，台南排列着千餘張椅子板凳。台前豎着兩根旗杆，旗杆頂上有
着碩大的旗鬥。校場裏聚集着數百個四袋以上的丐幫弟子。他們都是
來競選新任丐幫幫主的。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "north" : __DIR__"westjie3",
        ]));
        set("coor/x", -7850);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}