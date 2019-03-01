#include <ansi.h>

inherit ITEM;

void create()
{
        switch(random(13)) {
        case 0 : set_name(GRN"玉人頭飾"NOR, ({ "yu pei", "yu", "pei"})); break;
        case 1 : set_name(HIY"獸面紋玉琮"NOR, ({"yu pei", "yu", "pei"})); break;
        case 2 : set_name(HIW"三叉形玉器"NOR, ({"yu pei", "yu", "pei"})); break;
        case 3 : set_name(MAG"玉龍"NOR, ({"yu pei", "yu", "pei"})); break;
        case 4 : set_name(YEL"豬龍形玉佩飾"NOR, ({"yu pei", "yu", "pei"})); break;
        case 5 : set_name(WHT"玉龜"NOR, ({ "yu pei", "yu", "pei"})); break;
        case 6 : set_name(WHT"兔形玉佩"NOR, ({"yu pei", "yu", "pei"})); break;
        case 7 : set_name(YEL"虎形玉佩"NOR, ({"yu pei", "yu", "pei"})); break;
        case 8 : set_name(GRN"蛙形綠松石佩"NOR, ({"yu pei", "yu", "pei"})); break;
        case 9 : set_name(HIY"跪式玉人"NOR, ({"yu pei", "yu", "pei"})); break;
        case 10 : set_name(CYN"拱手玉人"NOR, ({"yu pei", "yu", "pei"})); break;
        case 11 : set_name(CYN"玉虎"NOR, ({"yu pei", "yu", "pei"})); break;
        case 12 : set_name(MAG"玉鳳"NOR, ({"yu pei", "yu", "pei"})); break;
        }
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("unit", "塊");
                set("weight", 1000);
		set("long", "這是東漢玉石飾品中的一個，出自陝西，山東，河南一帶。\n");
		set("material", "stone");
        set("base_value", 900000);
        set("value", 900000);
        }
	setup();
}
