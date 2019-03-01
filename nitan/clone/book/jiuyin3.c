// jiyin3.c

inherit BOOK;
inherit F_UNIQUE;
 
void create()
{
        set_name("「九陰真經」殘本", ({ "jiuyin zhenjing3" }));
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本手抄本，上面記錄了一些武功秘訣。\n");
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":        "yinlong-bian",
                        "exp_required": 100000,
                        "jing_cost" : 45,
                        "difficulty": 30,
                        "max_skill" : 179,
                ]) );
        }
}