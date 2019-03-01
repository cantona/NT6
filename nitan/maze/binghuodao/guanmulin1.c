inherit __DIR__"binghuodao";

void create()
{
        set("short", "灌木林");
        set("long",
"據說，凡是在蓬萊仙島的凡人在意外死亡後魂魄都不會離開身\n"
"這裡是冰火島西岸海灘，海浪拍打著海邊巨石。周圍是一望無際的\n"
"大海，東邊傳來陣陣巨大的聲響，地動山搖一般，似乎島上的火山\n"
"在不斷地噴發，釋放出巨大的能量。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenbingtan", 
                "southeast"   : __DIR__"shenmishandong",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/shixueyeren");
                
        setup();
}
