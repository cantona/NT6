#include <ansi.h>
inherit ITEM;

string book_name();
void create()
{
        set_name("不知名的書", ({"noname book"}));
        set_weight(10);
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一本破破舊舊的書，不知道是用什麼文字寫成的。\n");
                set("unit", "本");
                set("material", "paper");
                set("value", 2000);
                set("no_sell", 1);
                set("skill", ([
                        // "name":         (: book_name :),// name of the skill
                        "name":         "freezing-force",// name of the skill
                        "jing_cost":    100,            // jing cost every time study this
                        "difficulty":   50,             // the base int to learn this skill
                        "max_skill":    180,            // the maximum level you can learn
                ]) );
        }
}

string book_name()
{
        if( random(2) ) return "freezing-force";
        return "bingcan-duzhang";
}