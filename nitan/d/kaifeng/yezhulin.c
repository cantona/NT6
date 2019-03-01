inherit ROOM;

void create()
{
        set ("short", "野豬林");
        set("long", @LONG
自從不久前這林子中出了野豬之後，這片鬆林就少人來開封境內，
談豬色邊。只有為生活所迫的樵子還在林邊打些野柴。自認武藝高強
的圖個路近，也從此過。穿過此地便是華山。
LONG );

        set("outdoors", "kaifeng");
        set("exits", ([
                "northeast" : __DIR__"dadao2",
        ]));
        set("objects", ([
                "/clone/quarry/zhu" : 2,
                "/clone/quarry/zhu2" : 2,
        ]));
	set("coor/x", -5060);
	set("coor/y", 2090);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}