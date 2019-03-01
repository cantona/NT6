inherit ROOM;

void create()
{
        set("short",  "長江岸邊" );
        set("long", @LONG
這裡是長江北岸，江水在你身邊嘩嘩的流淌，不時可以看見有山
木從上遊漂來，在水中打了個圈，向下遊漂去。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "northup" : __DIR__"chibi3",
                "west" : __DIR__"chibi5",                
        ]));
        set("coor/x", -350);
        set("coor/y", -230);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
} 