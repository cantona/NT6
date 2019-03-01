// shenyangjiu.c 參陽玉酒
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

void init()
{
        if (!wizardp(this_player()))
        {
                set("no_give","這麼珍貴的酒，哪能隨便給人？\n");
                set("no_drop","這麼寶貴的美酒，扔了多可惜呀！\n");
                set("no_sell","這樣的美酒都要賣,你太不解風情了吧。\n");
        }
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}

void create()
{
        set_name( YEL "參陽玉酒" NOR , ({"shenyang yujiu", "jiu"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "壺");
                set("long","一壺金黃的粘稠藥酒，是凌霄城的珍藏，飲之于學武大有裨益。\n");
                set("value", 0);
                set("drug_type", "補品");
        }
        set("is_monitored",1);
        set("pour_type", "1");
        setup();
}

int do_drink(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要喝什麼？\n");
        if(!present(this_object(), this_player()))
                return notify_fail("你要喝什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢喝，小心別嗆著了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) )
        {
                write("你滿面紅光的，喝如此兇的酒不怕上火？\n");
                return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        message_vision(HIW "$N舉杯飲下參陽玉酒，只覺小腹間熱氣上沖，跟著胸口間便\n如火燒般熱了起來，只覺通體融和，四骸俱泰。\n" NOR, me);
        destruct(this_object());
        return 1;
}
