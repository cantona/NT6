// dizhangshi.c  地藏之石  武器原料，只能被 wizard 使用
// Written by Doing Lu 1998/11/3

inherit ITEM;

#include <ansi.h>

// 打造武器粗坯時需要的一種原料
// 根據 material_ attrib = x 為判斷標志，其有效點數為:power_point
// 地藏之石的有效點數是 1000

void create()
{
        set_name(YEL "地藏之石" NOR, ({"dizang zhishi", "shi"}));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊來自地府的石頭，亮晶晶的，閃耀著詭異的光芒，傳說可以用它制成" HIY "如意乾坤袋。\n" NOR);
                set("unit", "塊");
                //set("material_attrib", "x");
                set("power_point", 1000);
                set("value", 10000000);
                set("no_sell", 1);
        }
}

int query_autoload() { return 1; } 
