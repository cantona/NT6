// tuijianxin-2.c 推薦信 門-旗

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin2", "xin2", "letter2"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封門主為你寫的推薦信，憑此可去見五行旗掌旗使。\n");
                set("material", "paper");
        }
}
