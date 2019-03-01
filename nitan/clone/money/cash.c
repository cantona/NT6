// thousand.c

inherit MONEY;

void create()
{
        set_name("一千兩銀票", ({"cash", "thousand-cash", "cash_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "cash");
                set("long", "一張面額值一千兩銀子的銀票。\n");
                set("unit", "疊");
                set("base_value", 100000);
                set("base_unit", "張");
              set("base_weight", 1);
                set("material", "paper");
        }
        set_amount(1);
}

