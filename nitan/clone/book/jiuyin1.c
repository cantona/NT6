inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「九陰真經」上冊", ({ "jiuyin zhenjing1","zhenjing1", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
        "這是一本用薄絹寫成的書。上書：“九陰真經(上)”。\n"
        "書皮泛黃，看來已經保存很久了。\n",

        );
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "force",
                        "exp_required": 100000,
                        "jing_cost":  40,
                        "difficulty": 30,
                        "max_skill":  199,
                        "min_skill":  100
                ]) );
        }
}