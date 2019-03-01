inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰雪峽～谷");
        set("long",
"路的盡頭依然是一處巨大的峽谷，四周被高聳的山峰包圍，山\n"
"峰又被厚厚的積雪覆蓋，不時傳來幾聲巨大的吼叫，峽谷之後似乎\n"
"藏著巨大的神獸。\n"
);
        set("exits", ([ 
                "south"   : __DIR__"bingfengzhandao", 
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/binglong");
        
        setup();
}
