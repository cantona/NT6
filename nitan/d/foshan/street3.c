inherit ROOM;

void create()
{
        set("short", "大鎮街");
        set("long", @LONG
佛山自古與朱仙、景德、漢口並稱天下四大鎮，端的是民豐物阜，
市廛繁華。一條大街橫亙東西。南邊是南門，通往南海。北邊出北門
跨南嶺可達中原。
LONG );
        set("objects", ([
                "/d/city/npc/liumangtou": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"northgate",
                "south" : __DIR__"southgate",
                "west"  : __DIR__"street2",
                "east"  : __DIR__"street4",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}