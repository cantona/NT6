inherit ROOM;

string* books = ({
        "/clone/book/mizong_book",
        "/clone/book/skin",
        "/clone/book/book-bamboo",
        "/clone/book/book-silk",
        "/clone/book/book-stone",
        "/clone/book/book-iron",
        "/clone/book/skin-hammer",
});
void create()
{
        set("short", "藏經室");
        set("long", @LONG
 這裡是雪山寺的藏經室，靠牆是一排書架，擺滿了各種拳譜、書
籍。大多是當年掌門人鳩摩智翻譯的佛經和從少林寺取來的武學典籍。
LONG );
        set("exits", ([
                "north" : __DIR__"dating",
        ]));

        set("objects", ([
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
                CLASS_D("xueshan")+"/daerba" : 1,
        ]));
        setup();
        replace_program(ROOM);
}