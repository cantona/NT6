inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
這是一間存放兵器的屋子。刀、槍、劍、戟等各種兵器都
按類放在各自的兵器架上。整個屋子落滿灰塵，顯然已經好久
沒人來過。
LONG);
        set("exits", ([
                "west" : __DIR__"qianyuan",
        ]));
        set("objects", ([
                __DIR__"obj/taojian": 5,
        ]) );
        setup();
}