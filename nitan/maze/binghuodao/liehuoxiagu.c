inherit __DIR__"binghuodao";

void create()
{
        set("short", "烈火峽～谷");
        set("long",
"來到這裡，已經很難用辭藻來形容這裡的異象，天空中火光閃\n"
"耀，電閃雷鳴，不時又遮天蔽日，定睛一看，竟然是一條巨大火龍，\n"
"噴吐著火燄。火龍飛過，無數如流星雨般的火石從天而下……\n"
);
        set("exits", ([ 
                "north"   : __DIR__"huoyanshiqiao",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huolong");
        
        setup();
}
