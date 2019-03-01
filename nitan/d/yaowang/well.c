inherit ROOM;

void create()
{
        set("short", "水井");
        set("long", @LONG
這裡是一片青青的草地，邊上稀稀落落的長著幾根青竹，草
地中央有一口井，井邊的轆轤上掛著一只打水(fill)的木桶，奇
怪的是井台的的石頭上不知道被誰弄成了紅藍相間的顏色。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");

        set("resource", ([
        "water" : 1,            // 打水標記
        "condition" : "scorpion_poison",   // 水中有毒

        "count" : 12,           // 毒發時間
        "time" : -1,            // 水中毒的有效時間，-1 代表永遠有效
]));

        setup();
        replace_program(ROOM);
}
