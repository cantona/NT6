// Room: /d/songshan/shuzhai.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
#include <ansi.h>
int do_get();

string *book = ({
        "/clone/book/book-silk",
        "/clone/book/book-paper",
        "/clone/book/sword_book1",
        "/clone/book/sword_book4",
        "/clone/book/strike_book",
});

void create()
{
        set("short","書齋");
        set("long",@LONG
這裡是嵩山派的書齋，靠牆是一排書架，上面整整齊齊碼著一排排
書，大略看去各派武籍都有。南側靠窗處有張書桌，桌上四寶俱備。
LONG);
        set("exits",([
                "north" : __DIR__"eastting",
        ]));
        set("book_count", 2);
        set("coor/x", 0);
        set("coor/y", 890);
        set("coor/z", 90);
        setup();
}
void init()
{
        add_action("do_get", "chou");
        add_action("do_get", "qu");
}
int do_get()
{
        object ob, me=this_player();
        addn("qi", -5, me);
        if ((query("book_count") > 0) && (random(5) == 3))
        {
                ob=new(book[random(5)]);
                ob->move(me);
                message_vision(HIY"$N在書架上翻來翻去翻了半天，取下一本"+query("name", ob)+HIY"來。\n"NOR,me);
                addn("book_count", -1);
        }
        else 
                message_vision("$N在書架上翻來翻去翻了半天，也不知道在找啥。\n",me);
        return 1;
}