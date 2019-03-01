// daxiaochang.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "大校場");
        set("long", @LONG
這是一個位於終南山山腰的圓坪，四周群山環抱。山腳下有一座
大池。每年臘月，全真派便於此地舉行大校，以考察門下弟子在這一
年間的進境。往南是一條崎嶇的山道。往西是一條通往峰頂的山路。
往北行便是重陽宮。只見遠處十餘幢道觀屋宇疏疏落落的散處山間。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup"     : __DIR__"shijie1",
                "westup"      : __DIR__"shanlu13",
                "southdown"   : __DIR__"shanlu12",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/pi": 1,
        ]));

        set("coor/x", -3170);
        set("coor/y", 110);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}