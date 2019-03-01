// Room: /d/fuzhou/xiaochang.c
// Date: may.12 1998 Java
inherit ROOM;

void create()
{
        set("short", "校場");
        set("long", @LONG
福州校場為福建水師校場。場中點將樓上高掛“施”字黑鏽金邊帥
旗，刀槍耀日生輝。水師提督施琅施大人親率十萬雄兵，隔海相望，壯
心不已。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west"   : __DIR__"nanmendou",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -70);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}