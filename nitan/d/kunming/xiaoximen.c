inherit ROOM;

void create()
{
        set("short",  "小西門" );
        set("long", @LONG
這裏是昆明的西城門，俗稱小西門，來來往往各色人出出
進進，有遊客，有做買賣的，也不乏些江湖人士。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"xroad1",
                "east" : __DIR__"jinmafang",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/caifan" : 1,
                "/d/city/npc/bing" : 4,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16860);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}