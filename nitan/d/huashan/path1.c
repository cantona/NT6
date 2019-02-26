inherit ROOM;

void create()
{
        set("short", "華山腳下");
        set("long", @LONG
這便是五嶽中西嶽華山，巍然聳立於陝西省華陰縣城南。華山北
瞰黃河，南連秦嶺，五座山峯高低錯落，各據一方，其間又有一段若
斷若續的山嶺相連，疏密有度，神韻天成，遠遠望去，狀若巨朵青蓮，
外圍諸峯如蓮瓣，中間三峯似蓮蕊，因此山便因『花』得名，取名華
山。又因其西臨少華山，故華山又稱太華。它素有『奇峯天下第一山
』之稱，西面是一個小村，而由東穿過野豬林便可到達開封府。
LONG );
        set("exits", ([
                    "west" : "/d/village/eexit",
                    "north" : __DIR__"yuquan",
                    "southeast" : __DIR__"shaluo",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan" );

        setup();
        replace_program(ROOM);
}