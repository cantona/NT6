// d/qingcheng/bingqishi.c

inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
這是一間存放兵器的屋子。刀、槍、劍、戟等各種兵器都按類放在
各自的兵器架上。整個屋子落滿灰塵，顯然已經好久沒人來過。
LONG );
        set("exits", ([
                "south" : __DIR__"zoulang2",
        ]));
        set("objects", ([
                __DIR__"obj/chui" : random(3),
                __DIR__"obj/zhui" : random(2),
        ]) );
        set("coor/x", -8070);
        set("coor/y", -830);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}