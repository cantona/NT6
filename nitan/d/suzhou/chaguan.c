// Room: /d/suzhou/chaguan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "茶館");
        set("long", @LONG
你一走進來，就聞到一股茶香沁入心脾，精神為之一爽。幾張八仙
桌一字排開，坐滿了客人，或高聲談笑，或交頭接耳。幾個店夥計在一
旁伺候着客人們，在台後坐着一位老闆娘，正在彈着算盤。
LONG );
        set("resource/water", 1);
//        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                __DIR__"npc/lady2" : 1,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}