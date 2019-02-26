inherit ROOM;

void create()
{
        set("short", "迎客大廳");
        set("long", @LONG
你站在春月樓二樓的迎客大廳裏。滿耳的淫聲穢響不絕如縷。佈置的
絕對精緻的牀上地下，突然對你產生莫名的誘惑和衝動。幾個可憐兮兮的
千嬌百媚在點手招你，更有幾個騷媚十足的已經坐到了你的身旁，伸手勾
你了。四周有四個小廳，專供有錢客人和姑娘單處。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"chenyu",
                  "down" : __DIR__"jiyuan",
                  "south" : __DIR__"xiuhua",
                  "west" : __DIR__"luoyan",
                  "north" : __DIR__"biyue",
        ]));
        set("objects", ([
                "/d/beijing/npc/piaoke" : 1,
                "/d/beijing/npc/jinv" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}