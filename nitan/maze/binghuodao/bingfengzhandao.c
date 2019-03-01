inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰峰棧道");
        set("long",
"這裡是靠近峽谷的一處棧道，只見棧道竟由一根根冰柱連貫而\n"
"成。冰雪漫天，前方一片茫茫，似乎看不到盡頭。\n"
);
        set("exits", ([ 
                "south"   : __DIR__"bingfenggu", 
                "north"   : __DIR__"bingxuexiagu",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/binglangren");
        
        setup();
}
