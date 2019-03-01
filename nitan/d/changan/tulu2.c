// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條黃土飛揚的路，不算太寬，給人一種落寞的感覺，路邊
零零散散的分布著幾片小田地，偶然也能看得見一些炊煙。四周一片
的荒寂。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northup"   : "/d/changan/tulu3",
                "southwest" : "/d/changan/tulu1",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}