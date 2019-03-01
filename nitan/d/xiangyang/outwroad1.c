// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時有人騎著馬匆
匆而過。大道東邊通向襄陽城，南面一條小路通向一個山丘，西邊是
一條小河。
LONG );
        set("outdoors", "襄陽");

        set("exits", ([
              "southeast" : __DIR__"westgate1",
        ]));

        setup();
        replace_program(ROOM);
}
