// Room: /d/fuzhou/ximen.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
這裡是福州西門。一條筆直的官道向西延伸，直到西邊閩江大拐彎
處，官道便轉入北岸山坳處，直達中原。
LONG );
        set("exits", ([
                "east" : __DIR__"xixiaojie",
                "west" : "/d/yanping/guandao1",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -120);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}