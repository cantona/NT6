#include <ansi.h>

inherit ROOM;
string* books = ({
	"/clone/book/book-bamboo",
	"/clone/book/book-paper",
	"/clone/book/book-stone",
	"/clone/book/book-iron",
});


void create()
{
    set("short", "小屋");
    set("long", @LONG
一進小屋，只見牆上掛滿了無數名貴的字畫，書架上也堆滿了平
時難得一見的各種各樣的書籍。一個相貌英武的中年文士正對着一幅
字畫唉聲歎氣。
LONG
    );

    set("exits", ([
	"south" : __DIR__"caodi",

    ]));
    set("objects", ([
		CLASS_D("shenlong")+"/lu": 1,
		books[random(sizeof(books))] : 1,
		books[random(sizeof(books))] : 1,
    ]));
    set("outdoors", "shenlong");
    setup();
   replace_program(ROOM); 
}

