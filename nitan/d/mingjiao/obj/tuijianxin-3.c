// tuijianxin-3.c 推薦信 旗-堂

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin3", "xin3", "letter3"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封掌旗使為你寫的推薦信，憑此可去見五散人。\n");
                set("material", "paper");
        }
}
