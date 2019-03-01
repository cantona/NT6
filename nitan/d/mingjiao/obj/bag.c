// bag.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("油布包", ({ "bag", "bao" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個油布包裹。\n");
                set("value", 500);
                set("material", "cloth");
        }
        set("book_count", 0);
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_open", "open");
                add_action("do_open", "unpack");
                add_action("do_open", "dakai");
        }
}

int do_open(string arg)
{
        object me=this_player(), book;
        object where;

        if (! arg || ! id(arg))
                return 0;

        if( !query("jiuyang/zhang", me) )
        {
                write("什麼？\n"); 
                return 1; 
        }

        if (query("book_count") < 1)
        {
                write("油布包裡面什麼也沒有了。\n");
                return 1;
        }

        me = this_player();
        where = environment(me);
        message_vision("$N輕輕地把油布包來看時，裡面原來是一本"
                       "薄薄的經書，只因油布包得緊密，雖長期藏"
                       "在猿腹之中，書頁仍然完好無損。\n", me);
        book = new("/clone/book/jiuyang-book");
        book->move(file_name(where));
        addn("book_count", -1);
        return 1;
}
