
// 面具：為隱藏身份所佩帶

#include <armor.h>
#include <ansi.h>

inherit MYMASK;
 
void create()
{
        string *sname = ({
                "玉面修羅",
                "無名修羅",
                "紫煞修羅",
                "餓修羅",
                "七絕修羅",
                "金肢修羅",                
        });

        set_name(HIM "修羅面具" NOR, ({ "xiuluo mianju", "xiuluo", "mianju" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "tian jing");
                set("unit", "只");
                set("long", HIM "這是一隻面具，做成了修羅鬼王的模樣。戴上後便沒人知道你的真實身份了。\n" NOR);
                set("value", 1000000);
                /*
                set("armor_prop/mask_name", sname[random(sizeof(sname))]);
                set("armor_prop/mask_id",  ({ "masker xiuluo", "masker", "xiuluo"}) );
                set("armor_prop/mask_long", "此人佩帶着修羅面具，難以看出其真實身份。\n");
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


