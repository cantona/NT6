inherit ROOM;

void create()
{
        set("short", "龍亭大殿");
        set("long", @LONG
龍亭大殿原先是帝王行宮，後宋亡之後，宮殿頹廢，後人在此地
復建大殿，殿內珍寶林陳高檐直柱，令人歎為觀止。集南北宮殿建築
之大成。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road5",
                  "west" : __DIR__"tinyuan",
        ]));

	set("coor/x", -5070);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}