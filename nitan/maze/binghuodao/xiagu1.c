inherit __DIR__"binghuodao";

void create()
{
        set("short", "峽谷");
        set("long",
"這裡是一處平常的峽谷，峽谷蜿蜒前行，看看不到盡頭。不過\n"
"令人驚奇的是，峽谷北端寸草不生，南端卻草木茂盛，同一峽谷卻\n"
"有著兩種迥異的景象，真是匪夷所思。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"guanmucong", 
                "east"   : __DIR__"xiagu2",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/yeren");
        
        setup();
}
