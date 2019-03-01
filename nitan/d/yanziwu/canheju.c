//ROOM: /d/yanziwu/canheju.c

inherit ROOM;

void create()
{
        set("short", "參合居");
        set("long", @LONG
這是慕容世家首腦人物日常起居之地，布置得華麗中不乏清雅，
平實中透著高貴。楠木方桌，大太師椅，以及牆上的字畫都透著一股
非凡之氣。
LONG );
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("exits", ([
            "west" : __DIR__"qiushuan",
            "east" : __DIR__"zuijing",
            "north": __DIR__"yimen",
            "south": __DIR__"shuwu",
        ]));

        set("objects", ([
                CLASS_D("murong") + "/murongbo" : 1,
        CLASS_D("murong") + "/first" : 1,
        ]));
        setup();
        "/clone/board/murong_b"->foo();
}
