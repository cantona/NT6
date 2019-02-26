inherit ROOM;

void create()
{
        set("short", "三清殿");
        set("long", @LONG
這裏是凌霄宮的三清殿，是武當派會客的地點。供着元始天尊、
太上道君和天上老君的神像，香案上香煙繚繞。靠牆放着幾張太師椅，
地上放着幾個蒲團。東西兩側是走廊，北邊是練武的廣場，南邊是後
院。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "north" : __DIR__"guangchang",
                "south" : __DIR__"houyuan",
                "east"  : __DIR__"donglang1",
                "west"  : __DIR__"xilang",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/guxu" : 1,
                CLASS_D("wudang") + "/song" : 1
        ]));
        set("coor/x", -370);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
        "/clone/board/wudang_b"->foo();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "west" && dir != "south")
                return 1;

        if (! objectp(guarder = present("song yuanqiao", environment(me))))
                return 1;

        return guarder->permit_pass(me, dir);
}