// /d/beihai/shulin.c
// Last Modified by winder on May. 22 2002
inherit ROOM;

void create()
{
        set("short", "小樹林");
        set("long", @LONG
這是湖邊一片小松樹林，面積並不大。林中有一條小徑蜿蜒曲折向
西延伸開去。穿過這片松林就可以看見北海的前大門了。
LONG
        );
        set("exits", ([
                "west"  : __DIR__"qianmen",
                "north" : __DIR__"dongmen",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -170);
        set("coor/y", 4070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}