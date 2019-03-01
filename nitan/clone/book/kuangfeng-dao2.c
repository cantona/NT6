// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「狂風快刀」下冊", ({ "kuangfeng book2", "book2", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
        "這是一本發舊的秘籍。上書：“狂風快刀(下)”。\n"
        "書皮泛黃，看來已經保存很久了。\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "kuangfeng-blade",
                        "exp_required": 2500000,
                        "jing_cost" :  300,
                        "difficulty":  92,
                        "max_skill" :  200,
                        "min_skill" :  100
                ]) );
        }
}
