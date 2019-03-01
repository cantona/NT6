// Room: /d/shaolin/fzlou.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "方丈樓");
        set("long", @LONG
這裡的地上整整齊齊的排放著數十個黃布蒲團，北首有一個紅木
講壇，講壇上放著個竹制的木魚。東西邊各放著一對美輪美奐的大花
瓶，上插檀香數枝，香煙繚繞，氤氳芬芳，室內一片祥和之氣。看來
這裡是方丈對僧眾講經說法的地方。
LONG );
        set("exits", ([
                "south" : __DIR__"wuchang",
                "up" : __DIR__"fzlou1",
                "north" : __DIR__"wuchang3",
                "east" : __DIR__"zoulang7",
                "west" : __DIR__"zoulang6",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
