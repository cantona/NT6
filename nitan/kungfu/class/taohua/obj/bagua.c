// /kungfu/class/taohua/bagua.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(GRN"鐵八卦"NOR, ({ "tie bagua", "bagua" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","鐵八卦是純鐵所鑄，分量極重，上有八卦圖案。\n是桃花島弟子用來佔卜、推算(location)他人區位的道具。\n");
                set("unit", "枚");
                set("value", 1600);
        }
        setup();
}