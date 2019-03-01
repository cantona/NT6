// Room: /d/shaolin/zoulang5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是禪房走廊。走廊南側的房頂倚着南面的高牆，另一側凌空
架在幾根細細的石柱上，倚在欄杆上，北望是一大片竹林，馨香滿懷，
竹影搖曳，詩意頓上心頭，別有一番韻趣。
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang6",
                "north" : __DIR__"zhulin4",
                "southdown" : __DIR__"banruo9",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


