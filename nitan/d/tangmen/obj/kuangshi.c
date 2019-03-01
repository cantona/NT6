//kuangshi.c


inherit ITEM;

void create()
{
        set_name("鐵礦石", ({"kuang shi", "shi", "stone"}));
        set_weight(60000);
        set("unit", "塊");
        set("long", "這是一塊尚未冶煉的精鐵礦。\n");
        set("value", 1000);
        setup();
}