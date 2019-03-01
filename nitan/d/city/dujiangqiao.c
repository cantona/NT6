// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short","渡江橋");
        set("long",@LONG
一座三拱石橋橫臥在大運河上，橋的側欄上由知州歐陽修題著「渡
江橋」，橋下各色船只穿流不息。東邊是揚州最大的碼頭，漕運的糧食，
兩淮產的鹽，多在此裝卸。過了橋就是揚州的南門。
LONG );
        set("outdoors", "yangzhou");
        set("region", "yangzhou_zone");

        set("exits", ([
                "north"  : __DIR__"nanmen",
                "south"  : "/d/wudang/wdroad1",
                "west"  : __DIR__"shulin1",
                "east"  : __DIR__"matou",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shipopo" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
	set("coor/x", 0);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
