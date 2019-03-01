//ROOM: /d/yanziwu/jiashan.c

inherit ROOM;

void create()
{
        set("short", "假山");
        set("long", @LONG
怪石堆疊，巨石參差，你有些頭暈目眩，那麼多山洞你不知該鑽
哪一個。個個山洞都昏暗曲折，實在不知通向什麼地方。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "west" : __DIR__"zuijing",
            "east" : __DIR__"shuiyun",
            "north": __DIR__"huayuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}