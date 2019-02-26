inherit ROOM;

void create()
{
        set("short", "南嶺山口");
        set("long", @LONG
這裏是南嶺的一個山口。南面就是佛山了，北面是橫亙湖南廣東
的五嶺。這裏地氣非常炎熱，百物速生快長，口音也漸漸遠異中原了。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "northup" : "/d/henshan/hsroad9",
                "southwest" : "/d/yaowang/lcd01",
                "south"   : __DIR__"northgate",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}