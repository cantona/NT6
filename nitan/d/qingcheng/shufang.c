// d/qingcheng/shufang.c
inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這是一間幹幹凈凈的書房。當中一個大檀木桌，桌上放著不少書籍。
靠牆的地方還有一個書架，架上滿滿的全是各種封裝的書。其中不少書
看上去古意盎然，顯然年代已久。
LONG );
        set("exits", ([
                "north" : __DIR__"zoulang2",
        ]));
        set("objects", ([
                "/clone/book/laozi1": random(2),
                "/clone/book/laozi13": random(2),
                "/clone/book/daodejing-i": (int)(random(4)/3),
                "/clone/book/daodejing-ii": (int)(random(4)/3),
                "/clone/book/cheng18po": (int)(random(4)/3),
        ]) );
        set("coor/x", -8070);
        set("coor/y", -850);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}