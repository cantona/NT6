
// 面具：為隱藏身份所佩帶

#include <armor.h>
#include <ansi.h>

inherit MYMASK;
 
void create()
{
        string *sname = ({
                "天煞孤星",
                "無名孤星",
                "夙世孤星",
                "六道孤星",
                "天命孤星",
                "夜影孤星",                
        });

        set_name(HIW "孤星面具" NOR, ({ "guxing mianju", "guxing", "mianju" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "tian jing");
                set("unit", "只");
                set("long", HIW "這是一只面具，面具上繪著一顆奇特的星形圖案。戴上後便沒人知道你的真實身份了。\n" NOR);
                set("value", 1000000);
                /*
                set("armor_prop/mask_name", sname[random(sizeof(sname))]);
                set("armor_prop/mask_id",  ({ "masker guxing", "masker", "guxing"}) );
                set("armor_prop/mask_long", "此人佩帶著孤星面具，難以看出其真實身份。\n");
                set("armor_prop/mask_flag", 1);
                */
        }
        setup();
}

void init()
{
        add_action("do_exit", "exit");
        add_action("do_exit", "quit");
        add_action("do_exit", "save");
}

int do_exit()
{
        if (this_player()->query_temp("apply/mask_flag"))
        {
                return notify_fail("請取下面具後再進行該操作。\n");
        }
}

int query_autoload()
{
        return 1;
}


