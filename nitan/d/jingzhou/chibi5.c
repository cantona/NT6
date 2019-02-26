inherit ROOM;

void create()
{
        set("short",  "長江岸邊" );
        set("long", @LONG
這裏是長江北岸，江水在你身邊嘩嘩的流淌，偶爾你會在沙灘上
發現有一些殘刀斷戟，原來西邊不遠就是有名的古戰場赤壁。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"chibi4",
                "west" : __DIR__"chibi6",                
        ]));

             
        set("coor/x", -360);
        set("coor/y", -230);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
} 