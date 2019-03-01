inherit ITEM;
inherit F_FOOD;

void create()
{
        int i;
        string *names = ({ "石斑魚", "虎紋魚", "□魚" });
        i = random(3);
        set_name(names[i], ({ "fish" }) );
        set_weight(120);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一條剛剛釣上來的鮮魚。\n");
                set("unit", "條");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
}
