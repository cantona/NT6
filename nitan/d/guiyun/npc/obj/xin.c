// xin.c

inherit ITEM;

void create()
{
        set_name("書信", ({"guiyun shuxin", "shu xin", "xin"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封陸冠英寫的邀請進入歸雲莊的書信。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "paper");
        }
}
