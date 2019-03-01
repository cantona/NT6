inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「九陰真經」下冊", ({ "jiuyin zhenjing2","zhenjing2", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
        "這是一本用薄絹寫成的書。上書：九陰真經(下)”。\n"
        "筆法清秀脫俗，看來出于女子手筆。\n",
        );
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "jiuyin-baiguzhao",
                        "exp_required": 10000,
                        "jing_cost":  30,
                        "difficulty": 20,
                        "max_skill":  99,
                        "min_skill":  0
                ]) );
        }
}