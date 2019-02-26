// Room: /d/suzhou/hutong2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "衚衕");
        set("long", @LONG
這是一條黑暗、骯髒的小巷，空氣中彷彿飄揚着一股罪惡的氣息，
幾個賊眉鼠眼地盯着你的腰包，看來會馬上撲上來。北面是一條小巷，
名為“生死巷”。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"leitai",
                "east"      : __DIR__"hutong3",
                "southwest" : __DIR__"hutong1",
        ]));
        set("objects", ([
                "/d/city/npc/liumangtou" : 1,
                "/d/city/npc/liumang" : 2,
        ]));
	set("coor/x", 1130);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}