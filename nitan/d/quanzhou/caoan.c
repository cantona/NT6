// Room: /d/quanzhou/caoan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "草菴");
        set("long", @LONG
寺內有著名的摩尼石像。它面龐圓闊，眉彎隆起，散發披肩，身着
寬袍僧衣，雙手掌心向上置於膝上，神態莊嚴，別具風采。庵前約四米
處，巨石鶻立，中刻明教咒語，勸念：『清淨光明，大力智慧，無上至
真，摩尼光佛』。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"shangu",
        ]));
	set("coor/x", -931);
	set("coor/y", -7741);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}