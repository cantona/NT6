// midao6.c 石洞

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
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，地上和石壁滿是灰塵，看得出好久沒人來過了
靠左側石壁是一排書架，上面也滿是灰塵，還有一些破舊的書籍。
牆角有一張石床。雖然很臟，卻也能休息。
LONG );
        set("exits", ([
                "west" : __DIR__"midao7",
        ]));
        set("sleep_room", 1);
        set("objects", ([
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
        ]));
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}