// Feb. 6, 1999 by Winder
inherit ITEM;
void create()
{
        set_name( "情書", ({ "qing_shu"}));
        set("taskobj", 1);
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long", "這是阿土送給阿鳳的情書，你可不要私自打開來看哦。\n");
        }
}