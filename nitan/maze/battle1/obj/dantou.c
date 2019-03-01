// This program is a part of NT MudLIB

inherit ITEM;

void create()
{
        set_weight(30000);
        set_name("彈頭", ({"dan tou"}));
        set("long", "這是一枚炮彈彈頭。\n");
        set("unit", "枚");
              
        set("value",100);
        setup();
}
