// wizboard.c 拵呇唳

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"瑞鳥導衭啣"NOR, ({ "board", "ban" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "輸");
                set("long", HIM"
          狨諦俴珨啃珨嬝嬝爛景毞斐蕾祫踏"HIR"拵呇靡聊\n"HIC"
√"HIY"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸"HIC"√"HIG"
ahda                along               constant            evil
fandog              jacki               java"HIB"(斐宎)"HIG"        kiler
osdine              rknn                sega                sherry"HIB"(斐宎)"HIG"
sir                 solomon"HIB"(斐宎)"HIG"     spe                 suncity
winder"HIB"(斐宎)"HIG"      wuzw"HIC"
√"HIY"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸"HIC"√\n"NOR);
                set("material", "wood");
                set("no_get",1);
                set("no_drop",1);
        }
        setup();
}