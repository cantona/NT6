inherit ROOM;

void create()
{
        set("short", "延慶觀");
        set("long", @LONG
延慶觀飛檐挑拱，氣勢磅礡。始建于元太宗五年，原名為重陽觀，
為紀念道教中全真教創始人王吉在此傳教並逝世于此而修建。明洪武
六年，改名延慶觀。  
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"sanqing",
                  "east" : __DIR__"wroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5080);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}