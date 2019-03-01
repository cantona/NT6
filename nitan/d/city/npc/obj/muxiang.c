// muxiang.c 大木箱

inherit ITEM;

int is_muxiang() { return 1; }

void create()
{
        set_name("大木箱", ({ "da muxiang", "muxiang"}));
        set_weight(20000);
        set_max_encumbrance(2000000000);
        // set_max_carryitems(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個打造的結結實實的大木箱，上面還有貼著一張標簽。\n這個木箱最多可以存放200個物品。\n你可以使用 idlabel 指令修改木箱的ID。\n你可以使用 namelabel 指令修改木箱的名字。\n不要給木箱起亂七八糟的名字，否則你會受到各種可能的懲罰！\n");
                set("value", 10000);
        }
}

int is_container() { return 1; }