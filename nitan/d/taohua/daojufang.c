inherit ROOM;

void create()
{
        set("short", "道具房");
        set("long", @LONG
這是一間道具房。擺著一些桃花弟子們常用的東西。房裡
好象黑乎乎的，靠窗處有一張斑駁長桌和一把靠背椅，雖是白
天還點著小油燈。啞僕看到你進來，就使勁瞪著你，雖然口不
能言，可你還是心中惴惴。
LONG);
        set("exits", ([
                "west" : __DIR__"dating",
                "up"   : __DIR__"shufang",
        ]));

        if (random(5) > 3)
                set("objects", ([
                        __DIR__"npc/yapu"  : 2,
                        __DIR__"obj/bagua" : 1,
                        __DIR__"obj/xiang" : 1,
                        __DIR__"obj/zhuxiao" : 1,
                ]));
        else
        if (random(4) > 2)
                set("objects", ([
                        __DIR__"npc/yapu"  : 2,
                        __DIR__"obj/xiang" : 1,
                        __DIR__"obj/zhuxiao" : 1,
                ]));
        else
                set("objects", ([
                        __DIR__"npc/yapu"  : 2,
                        __DIR__"obj/zhuxiao" : 1,
                ]));

        setup();
}