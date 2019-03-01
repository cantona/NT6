// fu-xiaoyuan 富家小院
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "富家小院");
        set("long", @LONG
這是進門後的一個小院落。西面是一道側門，東面是一扇月
形門好象通往花廳，北面是大門，南面就是大堂了。幾個窮漢正
垂頭喪氣地站在小院中，可能是因為繳不起租被抓來了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "north" : __DIR__"fu-damen",
                "south" : __DIR__"fu-datang",
                "west" : __DIR__"fu-cemen",
                "east" : __DIR__"fu-huating",
        ]));
        set("objects", ([
                __DIR__"npc/poorman" : 2,
        ]));

        set("coor/x", -12240);
	set("coor/y", 790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}