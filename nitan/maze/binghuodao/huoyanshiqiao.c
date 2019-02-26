inherit __DIR__"binghuodao";

void create()
{
        set("short", "火焰石橋");
        set("long",
"這裏是位於火焰谷到烈火峽谷之間的一處石橋。這裏寸草不生。\n"
"抬頭之間，無數火紅的石塊帶着火焰墜落下來時卻變成了巨大的火\n"
"球，伴隨着巨大的聲響，地動山搖，令人驚魂難定。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"huoyangu",
                "south"   : __DIR__"liehuoxiagu",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/jinsefenghuang");
        
        setup();
}
