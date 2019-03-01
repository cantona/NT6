inherit ITEM;

void create()
{
        set_name( "少林英雄令", ({ "yingxiong ling", "ling", "iron" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊用於通行少林寺的鐵鑄令牌。 由方丈簽發，邀各路英雄入寺觀禮。\n");
                set("value", 100);
                set("material", "iron");
        }
        setup();
}

void init()
{
        call_out("dest", 1800);
}

void dest()
{
        destruct(this_object());
}