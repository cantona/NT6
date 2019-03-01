inherit ROOM;

void create()
{
    set("short", "墓道");
    set("long",@LONG
這是通往墓室的通道。通道十分寬敞，頂部懸掛著一顆大
大的夜明珠，照得整個墓道如同白晝。墓道盡頭便是墓室。
LONG);
        set("exits", ([
                "up"   : __DIR__"mudi",
                "down" : __DIR__"mushi",
        ]));
        set("objects", ([
                "/clone/book/luoshu" : 1,
                "/clone/book/hetu" : 1,
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}