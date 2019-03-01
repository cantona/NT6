// stone3.c

inherit ITEM;
void create()
{
        set_name("巖石", ({ "yan shi", "rock", "yanshi" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "一塊橫臥山麓，左厚右薄中空，
狀如古琴的巖石。泉水沖擊在巖石上，發出悅耳而有節奏的音響。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
