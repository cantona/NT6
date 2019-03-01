inherit ROOM; 
string* books = ({
        __DIR__"obj/book-bamboo",
        __DIR__"obj/book-silk",
        __DIR__"obj/book-stone",
        __DIR__"obj/book-iron",
});

void create()
{
        set("short","書房");
        set("long",@LONG
這裡是白自在的書房，一室之內，放滿了各類書籍。白自在
雖然狂妄自大，但說到他學問，卻當真也是飽讀詩書，學富五車。
這裡的書架，大大小小，總有十幾個吧。白自在的書童正在這為
他整理。
LONG);
        set("exits",([
            "north"  : __DIR__"weideju",
            "south"  : __DIR__"bridge",
        ]));
        set("objects", ([  
                __DIR__"npc/su" : 1,
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
        ]));
        setup(); 
        replace_program(ROOM);
}
