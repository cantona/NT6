// /yubifeng/songlin3.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "大鬆林");
        set("long", @LONG
這是一片茂密的鬆林，雜亂的生長在傾斜的山坡上。林中鬆樹都是
數百年的老樹，枝柯交橫，樹頂上壓了數尺厚的白雪，是以林中雪少，
反而好走。
LONG );
        set("exits", ([
                "east"  : __DIR__"songlin1",
                "west"  : __DIR__"songlin1",
                "north" : __DIR__"songlin2",
                "south" : __DIR__"songlin4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6110);
        set("coor/y", 5190);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}