// Room: /d/fuzhou/taxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "塔巷");
        set("long", @LONG
原名修文巷，宋代改稱興文巷、文興巷。以閩國時建育王塔於巷北
而改今名。塔系木構，後不知毀於何時。清代在巷內砌造半爿小塔，作
為古蹟紀念。
LONG );

        set("exits", ([
                "west"    : __DIR__"nanhoujie3",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}