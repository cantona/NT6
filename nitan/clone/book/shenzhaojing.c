// shenzhao-jing.c

#include <ansi.h>

inherit BOOK;

void create()
{
        set_name(MAG "神照經" NOR, ({ "shenzhao jing", "jing", "book"})); 
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張很普通的紙，上面抄錄了一些口訣，似乎是一"
                            "種叫做神照經\n的絕世武功訣竅。\n");
                set("material", "paper");
                set("skill", ([
                        "name"        :  "shenzhaojing",
                        "family_name" : "血刀門",
                        "exp_required":  100000,
                        "jing_cost"   :  30,
                        "difficulty"  :  25,
                        "max_skill"   :  400,
                ]));
        }
}
