// 冰魄銀針。/d/quanzhou/npc/obj/yinzhen.c
// Spacenet@FXLT 1.1.2000

#include <weapon.h>;
#include <ansi.h>;
inherit THROWING;

void init()
{
        add_action("do_bawan", "bawan");
}

void create()
{
        set_name(HIC"冰魄銀針"NOR, ({ "ice_sting", "zhen" })); 
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這就是武林中人聞之色變的冰魄銀針，針身縷刻花紋，打造得極是精細，令人忍不住想把玩(bawan)一番。\n");
                set("value", 0);
                set("base_unit", "根");
                set("base_weight", 30);
                set("base_value", 0);
                set("meterial", "iron");
                set("wield_msg", "$N小心翼翼地取出一根冰魄銀針當武器。\n");
                set("unwield_msg", "$N把銀針放回衣囊中。\n");
        }
        set_amount(1);
        init_throwing(25);
        setup();
}

int do_bawan()
{
        object me=this_player();

        if(!present(this_object(), me))
                return notify_fail("你要把玩什麼？\n");
        if ((int)this_player()->query_condition("ice_sting") < 10)
        {
                tell_object(this_player(), "你看着手中的銀針覺得有趣，把針身的花紋細細摸了一遍。\n");
                tell_object(this_player(), HIB "你突然覺得手掌麻麻的有些不太靈便，猛然驚覺：“針上有毒，如此把玩，豈不危險？”忙張開手掌\n拋下銀針，只見兩手掌心已深黑如墨，手臂麻木感漸漸上升，心中大駭，忍不住便要哭出聲來。\n" NOR);
                this_player()->apply_condition("ice_sting", 30);
        }        
        destruct(this_object());
        return 1;
}