// tieyanling.c 鐵焰令

inherit ITEM;

void create()
{
        set_name("鐵焰令", ({"tieyan ling", "tieyan", "ling"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long","這是一面黑黝黝的令牌，由教主簽發，憑此可向尊長挑戰。\n");
                set("material", "steel");
        }
}
