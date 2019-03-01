// xishanxinglvtu.c
// Last Modified by winder on Nov. 17 2000

inherit ITEM;

void create()
{
        set_name("溪山行旅圖", ({ "painting", "xi shan xing lv tu", "tu" }) );
        set("long","這是據說已經失傳了的范寬真跡，對于愛畫之人，算是無價之寶了。\n");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "幅");
                set("no_get", "那是無價之寶，對方連睡覺都揣在懷裡的！\n");
                set("no_drop", "這可是無價之寶，你這麼老大一個人，居然如此不識貨？！\n");
                set("value", 10000);
                set_weight(20);
//                set("treasure", 1);
        }
        setup();
}
