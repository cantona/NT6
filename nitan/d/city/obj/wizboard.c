// wizboard.c 巫師版

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"風塵舊友板"NOR, ({ "board", "ban" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIM"
          俠客行一百一九九七年春天創立至今"HIR"巫師名冊\n"HIC"
≡"HIY"────────────────────────────────"HIC"≡"HIG"
ahda                along               constant            evil
fandog              jacki               java"HIB"(創始人)"HIG"        kiler
osdine              rknn                sega                sherry"HIB"(創始人)"HIG"
sir                 solomon"HIB"(創始人)"HIG"     spe                 suncity
winder"HIB"(創始人)"HIG"      wuzw"HIC"
≡"HIY"────────────────────────────────"HIC"≡\n"NOR);
                set("material", "wood");
                set("no_get",1);
                set("no_drop",1);
        }
        setup();
}