// /guanwai/yuzhu.c

inherit ROOM;

void create()
{
        set("short", "玉柱峰");
        set("long", @LONG
白雲峰西南，有峰高聳挺秀，多峰突起，形如玉柱。東麓瀉出一水，懸
流如線，注入天池，就是古籍所載的“金線泉”了。
LONG );
        set("exits", ([
                "north"      : __DIR__"tiyun",
                "northeast"  : __DIR__"baiyun",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}