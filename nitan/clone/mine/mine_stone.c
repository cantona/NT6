// mine_stone.c

#include <mine_def.h>

inherit ITEM;

protected string mine_class, ucheck_long, unit = "兩";
protected int eff_weight, check_flag;

int no_save_in_home() { return 1; }
int is_mine_stone() { return 1; }
int query_check() { return check_flag; }
string query_long();
void set_unit(string arg) { unit = arg; }

varargs int set_check_flag(int flag)
{
        if(check_flag)
                return 0;

        if(flag && eff_weight)
        {
                eff_weight = eff_weight*8/10;
                if(eff_weight < 1)
                        eff_weight = 1;
        }

        if(mine_class == BLACK_IRON)
                unit = "錢";

        return check_flag = 1;
}

void create()
{
        switch (random(3))
        {
                case 0:
                        set_name("小礦石", ({ "ore" }) );
                        ucheck_long = "一小塊礦石。\n";
                        set_weight(10000);
                        break;
                case 1:
                        set_name("礦石", ({ "ore" }) );
                        ucheck_long = "一塊礦石。\n";
                        set_weight(15000);
                        break;
                case 2:
                        set_name("大礦石", ({ "ore" }) );
                        ucheck_long = "一大塊礦石。\n";
                        set_weight(20000);
                        break;
        }

        set("unit", "塊");
        set("material", "stone");
        set("long", evaluate((: query_long :), this_object()));
        setup();
}

string query_long()
{
        string cm;

        if(!check_flag)
                return ucheck_long;

        if(!mine_class
        || (eff_weight < 1)
        || !(cm = MINE_D->chinese_mine_class(mine_class)))
                return "這塊石頭裡不含任何礦物成分。\n";

        return sprintf("這是一塊含有%s的礦石，\n大約含有 %d %s%s。\n",
                cm, eff_weight, unit, cm);
}

void set_mine_class(string cs)
{
        if(!previous_object() ||
        (!sscanf(file_name(previous_object()), "/d/%*s")
        && (geteuid(previous_object()) != ROOT_UID)) )
                return;

        mine_class = cs;

}

string query_mine_class() { return mine_class; }

void set_eff_weight(int n)
{
        if(!previous_object()
        || (n < 0)
        || (!sscanf(file_name(previous_object()), "/d/%*s")
        && (geteuid(previous_object()) != ROOT_UID)) )
                return;

        eff_weight = n;
}

int query_eff_weight() { return eff_weight; }
