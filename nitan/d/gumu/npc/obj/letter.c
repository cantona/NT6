// letter.c

inherit ITEM;

void create()
{
        set_name("信", ({"long xin", "xin", "letter"}));
        set_weight(100);
        set("value",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封楊過給小龍女的書信。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "paper");
        }
}
