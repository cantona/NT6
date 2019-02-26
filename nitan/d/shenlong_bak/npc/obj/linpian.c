#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "蛇精鱗片" NOR, ({"shejing linpian", "shejing", "linpian"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一片從蛇精身上獲取的鱗片，是勇者的象徵。\n" NOR);
                set("unit", "片");
        }
}

int query_autoload()
{
        return 1;
}

