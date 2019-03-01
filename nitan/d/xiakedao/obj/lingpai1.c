// lingpai1.c 賞善罰惡令

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name("賞善罰惡令", ({ "ling pai", "pai" }));
        set("long", "這是一塊深灰色的令牌，正面有一張笑臉，刻有賞善兩個大字。\n"+
         "反面有一張生氣的表情，刻有罰惡兩個大子。這便是江湖上傳說的賞善罰惡令。\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 50000);
                set("material", "玉");
                set("armor_prop/armor", 2);
        }
        setup();
}