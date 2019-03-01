inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裡是一條林間小道，在樹叢中蜿蜒。東面就是泉州城的西門吊
橋，向西南可達嶺南廣東。
LONG );
        set("objects", ([
                __DIR__"obj/hua3": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "east"      : "/d/quanzhou/westbridge",
                "southwest" : __DIR__"road13",
        ]));
	set("coor/x", -6480);
	set("coor/y", -9720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}