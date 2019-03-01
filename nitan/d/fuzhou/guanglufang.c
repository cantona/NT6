// Room: /d/fuzhou/guanglufang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "光祿坊");
        set("long", @LONG
北宋熙寧元年(1068年)以光祿大夫身份任福州知州的程師孟，常到
坊裡的法禪寺遊覽，見池畔有一塊大巖石，便登石吟詩，故被稱為“光
祿吟台”，而此坊也改名為光祿坊。程師孟題吟的“光祿吟台”四個篆
字石刻今尚存。
LONG );
        set("exits", ([
                "east" : __DIR__"nanhoujie5",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -100);
	set("coor/y", -6230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}