// tuijianxin-4.c 推薦信 堂-王

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin4", "xin4", "letter4"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封五散人為你寫的推薦信，憑此可去見護教法王。\n");
                set("material", "paper");
        }
}
