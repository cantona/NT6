inherit ROOM;

void create()
{
        set("short",  "東門" );
        set("long", @LONG
這裏便是昆明的東城門，來來往往各色人出出進進，有遊
客，有做買賣的，也不乏些江湖人士。西邊可以看見碧雞枋。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"bijifang", 
                "east"  :__DIR__"qingshilu2",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/city/npc/bing" : 4,
        ]));
	set("coor/x", -16820);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}