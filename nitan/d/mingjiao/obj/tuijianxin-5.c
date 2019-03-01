// tuijianxin-5.c 推薦信 王-使者

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin5", "xin4", "letter5"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封護教法王為你寫的推薦信，憑此可去見光明使者。\n");
                set("material", "paper");
        }
}
