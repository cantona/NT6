inherit ROOM;

void create()
{
        set("short", "南門");
        set("long", @LONG
這裡便是昆明的南門，高高的城樓上寫著大大的南門兩個
字，由此南去，就是滇池了，出入南門的人很少，只有些漁民
不時提著新鮮的魚進城來賣。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "south" : __DIR__"htroad1",
                "north" : __DIR__"nandajie2",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/city/npc/bing" : 4,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}