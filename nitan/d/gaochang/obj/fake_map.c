// fake_map.c

inherit ITEM;

void create()
{
        set_name("高昌迷宮地圖", ({ "map", "ditu" }));
        set_weight(200);
        set("unit", "張");
        set("long", "這是一張絲織高昌迷宮地圖，高昌迷宮危險無比。
據說，須按：東，東，南，東，北，北，西，東，南，
方可進入。\n不過這副圖好象被抽走幾條絲線......\n");
        set("value", 5);
        set("material", "silk");
}
