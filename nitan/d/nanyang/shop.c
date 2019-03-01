// Room: /d/nanyang/shop.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short","商號");
        set("long",@LONG
一間不大的店舖，進門就是一個黃柏木未塗漆的櫃台，雖然擦拭得
很幹凈，但是顯見是多年之物了，木質都已作深黃。上面一把算盤，一
個茶吊。櫃台一側陳列著些雜飾，玉板，銀環，珠簪，折扇，應有盡有。
牆上掛著幾幅字畫。
LONG);
        set("exits",([
                "east"  : __DIR__"dajie1",
        ]));
        set("objects",([
                __DIR__"npc/boss" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}