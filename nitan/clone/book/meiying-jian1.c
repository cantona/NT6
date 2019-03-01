
// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「魅影劍法」上冊", ({ "meiying book1", "book1", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
        "這是一本發舊的秘籍。上書：“「魅影劍法」上冊”。\n"
        "書皮泛黃，看來已經保存很久了。\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "meiying-jian",
                        "exp_required": 20000000,
                        "jing_cost" :  200,
                        "difficulty":  50,
                        "max_skill" :  100,
                        "min_skill" :  0
                ]) );
        }
}
