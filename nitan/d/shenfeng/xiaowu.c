inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這地方極是乾燥，草木不生，屋中物品雖然經歷了不知多
少年月，但大部仍然完好。廳上有一雙女人的花鞋，色澤仍是
頗為鮮豔，想拿起來細看，哪知觸手間登時化為灰塵，不由得
嚇了一大跳。
LONG);

        set("exits", ([
                "south" : __DIR__"feixu2",
        ]));

        setup();
        replace_program(ROOM);
}