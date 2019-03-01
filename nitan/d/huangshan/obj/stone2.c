// stone2.c

inherit ITEM;

void create()
{
        set_name("醉石", ({ "zui shi", "drunk stone", "shi", "stone" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        set("prep","under");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "李白醉酒臥眠的醉石，石上一人形依稀可見，觀其形狀恰似
酒至酣處。\n");
                set("value", 1);
                set("skill", ([
                        "name"         : "literate",
                        "exp_required" : 0,
                        "sen_cost"     : 30,
                        "difficulty"   : 20,
                        "max_skill"    : 49
                ]) );
        }
}
int is_container() { return 1; }