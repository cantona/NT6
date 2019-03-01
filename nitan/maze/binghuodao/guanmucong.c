inherit __DIR__"binghuodao";

void create()
{
        set("short", "灌木叢");
        set("long",
"濃密的灌木叢，不合時宜的生長在此處，似乎是受到了一些特\n"
"殊的環境所影響，灌木叢中隱約有什麼奇怪的響動。\n"
);
        set("exits", ([ 
                "west"    : __DIR__"shadi", 
                "east"    : __DIR__"xiagu1", 
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/juxingshanzhu");
                
        setup();
}
