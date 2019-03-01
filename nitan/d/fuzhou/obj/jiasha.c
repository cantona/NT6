// jiasha.c

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_move", "move");
}

void create()
{
        set_name("袈裟", ({"jia sha", "jia", "sha"}));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一件舊得已經看不出顏色的袈裟，上面有好多窟窿。\n");
                set("unit", "件");
                set("material", "cloth");
                set("no_get", "這樣東西不能離開那兒。\n");

        }
        setup();
}

int do_move(string arg)
{
        object book;
        object me = this_player();
        if (!id(arg))
                return 0;
        if( query("passwd", this_player())){
                if (!present("kuihua baodian",me)){
                message_vision(
"$N輕輕地挪動袈裟，抖起一些塵土...，突然從袈裟的窟窿中滾出一本書到$N懷中。\n", this_player());
                book = new(BOOK_DIR"kuihua");
                book->move(me);
                return 1;
                }
                message_vision(
"$N輕輕地挪動袈裟，抖起一些塵土，嗆得$N直打噴嚏。\n", this_player());
                return 1;
        }
        else {
                message_vision(
"$N輕輕地挪動袈裟，突然從袈裟的窟窿中冒出一股毒氣，鑽進$N的鼻子中。\n", this_player());
                me->die();
                return 1;
        }
}
