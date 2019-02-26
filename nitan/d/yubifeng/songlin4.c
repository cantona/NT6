// /yubifeng/songlin4.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "大松林");
        set("long", @LONG
這是一片茂密的松林，雜亂的生長在傾斜的山坡上。林中松樹都是
數百年的老樹，枝柯交橫，樹頂上壓了數尺厚的白雪，是以林中雪少，
反而好走。
LONG );
        set("exits", ([
                "west"  : __DIR__"songlin5",
                "east"  : __DIR__"songlin3",
                "north" : __DIR__"songlin3",
                "south" : __DIR__"songlin2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6110);
        set("coor/y", 5180);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me = this_player();
        if (random(5) == 1)
        set("exits", ([
                "west"  : __DIR__"songlin5",
                "east"  : __DIR__"xiaolu1",
                "north" : __DIR__"songlin3",
                "south" : __DIR__"songlin2",
        ]));
}
