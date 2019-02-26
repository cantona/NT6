// bag.c
#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name("油布包", ({ "bag", "bao" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個油布包裹。\n");
                set("value", 500);
                set("material", "cloth");
        }
        set("book_count", 1);
}

void init()
{
        if( this_player() == environment() )
        {
                add_action("do_open", "open");
                add_action("do_open", "unpack");
                add_action("do_open", "dakai");
        }
}

int do_open(string arg)
{
        object me, book;
        object bag;
        object where;

        if ( !arg ) return 0;
        if ( query("book_count") < 1)
        {
                return notify_fail("油布包裏面什麼也沒有了。\n");
        }

        me = this_player();
        if ( arg == "bag")
        {
                where = environment(me);
message("channel:rumor",MAG"【謠言】某人："+query("name", this_player())+"找到九陽真經啦。\n"NOR,users());
                message_vision(
"$N輕輕地把油布包來看時，裏面原來是四本薄薄的經書，只因油布包得緊密，雖
長期藏在猿腹之中，書頁仍然完好無損。\n", me);
                book = new("/clone/book/jiuyang1");
                book->move(file_name(where));
                book = new("/clone/book/jiuyang2");
                book->move(file_name(where));
                book = new("/clone/book/jiuyang3");
                book->move(file_name(where));
                book = new("/clone/book/jiuyang4");
                book->move(file_name(where));
                addn("book_count",-1);
                bag = new(__DIR__"bag1");
                bag->move(environment());
                destruct(this_object());
        }
        return 1;
}