//d/xueshan/obj/tonggang.c
//tong gang


#include <ansi.h>

inherit ITEM;
inherit "/d/xueshan/inherit/liquid_container.c";

int burn_out_gang();

void create()
{
                object suyou;

        set_name(HIY "遍照雪海" NOR, ({"tong gang", "gang"}));
        set_max_encumbrance(600000000);
        set_weight(300000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "尊");
                set("long", 
                "一尊通體鍍金的銅缸。缸上雕刻著□遍照雪海佛□像。相傳\n"
                "這尊雕像是佛的受用身，受天下信徒崇拜。佛身上鑲嵌著五\n"
                "種天上的珠寶，五種地上的珠寶和五百零一種不同的水晶石。\n"
                "喇嘛們和信徒們敬奉的酥油都儲存在這裡。\n");
                set("value", 10000);
                                set("material","bronze");
                                set("no_get",1);
                        // make it doesn't refresh the butter
                set("no_refresh",1);
        }

                // mark it as a liquid container
                set("liquid/container",1);
                set_max_liquid(50000);
                set_current_liquid(0);
                set("liquid/unique",1);
            set("liquid/uniqueid","su you"); 

                setup();

        carry_liquid("/d/xueshan/obj/suyou", 12000);

}

int burn_out_gang()
{
        object *inv;
        int i;

        inv = all_inventory(this_object());
        
        message_vision(HIR"銅缸中的酥油一點就燃，熊熊烈火沖天而起。\n"NOR, this_object());

        for( i=0; i<sizeof(inv); i++ )
        {
              destruct(inv[i]);
        }
        this_object()->set_current_liquid(0);

        return 0;
}
