// damo-ling.c 達摩令

inherit ITEM;

void create()
{
        set_name("達摩令", ({"damo ling", "letter", "ling"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long","這是一面金光閃閃的令牌，由方丈簽發，憑此可弟子自由向師尊挑戰。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "steel");
        }
}
