// Room: /d/suzhou/lingyanta.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "靈巖塔");
        set("long",@long
靈巖塔，又名永多寶佛塔，始建於樑代。高約三十多米，為七級八
面塔。塔身上刻寫着“靈巖塔”三個大字。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "west"   : __DIR__"lingyansi",
//                "westup" : __DIR__"sdhyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1130);
	set("coor/y", -1160);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}