// tuijianxin-1.c 推薦信 壇－門

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin1", "xin1", "letter1"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封壇主為你寫的推薦信，憑此可去見接引使者。\n");
                set("material", "paper");
        }
}
