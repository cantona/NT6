#include <ansi.h>

inherit ITEM;

void create()
{
         switch(random(7)) {
        case 0 : set_name("牛文明墓畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 1 : set_name("車騎過橋畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 2 : set_name("狩獵畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 3 : set_name("橋頭交戰畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 4 : set_name("鬥獸畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 5 : set_name("兩桃殺三士畫像石", ({ "xiang shi", "shi", "stone"})); break;
        case 6 : set_name("比武畫像石", ({ "xiang shi", "shi", "stone"})); break;
        }
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("weight", 1000);
                set("long", "這是東漢石雕像中的一個，出自陝西，山東，河南一帶。\n");
                set("material", "stone");
                }
        setup();
}