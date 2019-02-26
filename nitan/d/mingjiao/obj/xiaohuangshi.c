// Code of JHSH
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("硝磺石", ({ "xiaohuang shi", "shi" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊硝磺石，是製作火槍和火藥的必須品。\n");
                set("unit", "塊");
//                                set("no_drop",1);

        }

}