// iron_cu.c

#include <mine_def.h>

inherit ITEM;

string query_long();

int is_iron_class_res() { return 1; }
string query_mine_class() { return IRON_RES_CU; }
int query_mine_value();

void create(int arg)
{
        set_name("粗鐵錠", ({ "cast iron ingot" }) );
        set_weight(0);

        if(intp(arg) && (arg >= 100))
                set_weight(arg);

        set("value", evaluate((: query_mine_value :),this_object()) );
        set("unit", "塊");
        set("long", evaluate((: query_long :), this_object()));
}

int query_mine_value()
{
        int wt;

        if( (wt = query_weight()) < 100 )
                return 0;

        return MINE_D->query_mine_class_value(IRON_RES_CU)*query_weight()/100;
}

string query_selling_msg()
{
        int w = query_weight();

        if(w < 100)
                return "一錢不值";
        else
                return sprintf("%d 兩重", w/100);
}

string query_long()
{
        int w = query_weight();
        string l = "這是一塊粗鐵錠，";

        if(w < 100)
                l += "看起來\n一錢不值。\n";
        else
                l += sprintf("大約\n有 %d 兩重。\n", w/100);

        return l;
}

int query_save_args()
{
        return query_weight();
}
