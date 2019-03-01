inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰峰谷");
        set("long",
"這裡是一處險要的峽谷，整個峽谷被冰雪覆蓋，漫天雪花，盡\n"
"是白茫茫一片。不時傳來幾聲狼嚎，令人毛骨悚然。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"bingfenggu", 
                "east"   : __DIR__"xuanwutai",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/binglang");    
        setup();
}
