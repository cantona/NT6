// tuijianxin-2.c 推薦信 道-慧

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin2", "xin2", "letter2"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封道字輩師尊們為你寫的推薦信，憑此可直接向慧字輩高僧們學習武藝。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "paper");
        }
}
