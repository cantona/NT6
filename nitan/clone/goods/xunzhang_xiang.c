
#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIM"紫金勛章箱子"NOR,({"xiang"}));
        //這個一定要設置：
        set("BAOXIANG_LIST",([
                "/clone/goods/practice-emblem":600,   //物品文件名:概率
                "/clone/goods/derive-emblem":150,   //物品文件名:概率
                "/clone/goods/research-emblem":150,   //物品文件名:概率
                "/clone/goods/research-emblem2":100,   //物品文件名:概率
        ])); //概率是以1000作為總數，且幾項的概率總和為1000，概率大的出現幾率高。。。
        
        set("long", HIY "這是一只金色的寶箱，裝飾的珠光寶氣，你或許可以打開（open）它。\n" NOR); 
        set("unit", "些");
        set("base_unit", "個");
        set("no_give",1);
        set("no_drop",1);
        set("base_weight",1);
        set("base_value",1);
        set_amount(1); //因為是個combined物品 所以這個一定要設置，不然報錯的

}
void init()
{
        add_action("do_open","open"); //玩家使用的接口 具體內容在std裡
        add_action("do_test","test"); //用于巫師測試用 測試ok請注釋此行
}

