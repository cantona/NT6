// shufang.c
inherit ROOM;

string* books = ({
        "/clone/book/book-bamboo",
//        "/clone/book/book-paper",
        "/clone/book/book-silk",
        "/clone/book/book-stone",
        "/clone/book/book-iron",
});

void create()
{
        set("short", "書房");
        set("long", @LONG
這裡是書房，靠牆是一排書架，擺滿了當今武林各個門派的武功
密藉。石洞中間放著石桌和幾個石凳，俠客島龍木二島主常常在這裡
讀書。
LONG );
        set("exits", ([
                "west" : __DIR__"dating"
        ]));
        set("objects", ([
                books[random(sizeof(books))] : 1,
        ]));
        set("coor/x", -3070);
        set("coor/y", -22110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}