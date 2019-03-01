// Room: /d/shaolin/zoulang8.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裡是禪房走廊。走廊南側的房頂倚著南面的高牆，另一側凌空
架在幾根細細的石柱上，倚在欄桿上，北望是一大片竹林，馨香滿懷，
竹影搖曳，詩意頓上心頭，別有一番韻趣。
LONG );
        set("exits", ([
                "west" : __DIR__"zoulang7",
                "north" : __DIR__"zhulin1",
                "southdown" : __DIR__"luohan9",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
