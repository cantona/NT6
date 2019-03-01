// weiqi.c 圍棋

#include <armor.h>

inherit ITEM;

void create()
{
        set_name("圍棋", ({ "wei qi", "weiqi", "qi", "go" }));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long",
                        "這是一副圍棋，棋盤用磁鐵所制，棋子用鐵鑄成。\n");
                set("value", 5000);
                set("material", "steel");
                set("armor_prop/armor", 10 );
        }
}
