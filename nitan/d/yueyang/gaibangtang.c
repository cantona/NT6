// Room: /d/yueyang/gaibangtang.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "大屋");
        set("long", @LONG
這裏是丐幫幫眾聚會場所，地上橫七豎八排着不少草蒲團。雖然看
起來似乎很凌亂，其實卻甚是合乎幫規：何人做何職司，前後順序，一
目瞭然。
LONG );
        set("exits", ([
                "south" : __DIR__"gaibangyuan",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/qiao-feng" : 1,
        ]));
        set("valid_startroom", 1);
	set("coor/x", -6210);
	set("coor/y", -2980);
	set("coor/z", 0);
	setup();
        "/clone/board/gaibang_b"->foo();
        replace_program(ROOM);
}