// Room: /d/huanggong/huangjidian.c

inherit ROOM;

void create()
{
        set("short", "皇極殿");
        set("long", @LONG
這裡是宮中僅次于御花園的乾隆花園的中心。皇極殿前是寧壽門，
後通寧壽宮，就是俗稱“外東路”的太上皇修身怡性處。
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "north"     : __DIR__"ningshougong",
                "south"     : __DIR__"ningshoumen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}