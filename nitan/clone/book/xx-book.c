// xx-book.c

inherit BOOK;

void create()
{
        set_name("拓本", ({ "tuo ben" , "book"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張很普通的紙，上面抄錄了一些口訣，似乎是一"
                            "種叫做吸星大法\n的內功訣竅。\n");
                set("material", "paper");
                set("skill", ([
                        "name"        :  "xixing-dafa",
                        "exp_required":  100000,
                        "jing_cost"   :  20,
                        "difficulty"  :  20,
                        "max_skill"   :  200,
                ]));
        }
}
