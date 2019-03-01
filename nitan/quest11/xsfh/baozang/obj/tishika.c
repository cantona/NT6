// by tangfeng 8/2004

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"提示卡"NOR, ({ "tishi ka", "ka", "paper"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是來自巫師的東西，似乎和冷泉神功有關。\n\n"
                            +"提示一：有其他內功為情況下，學習冷泉神功速度減半。\n"
                            +"提示二：學會冷泉神功後，胡家刀法和苗家劍法才能發揮真正的威力。\n"
							+"提示三：尋找紙團，VIP兩次機會，普通玩家一次機會。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
}
