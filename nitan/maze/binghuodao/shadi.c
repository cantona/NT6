inherit __DIR__"binghuodao";

void create()
{
        set("short", "沙地");
        set("long",
"這裡是一片沙地，是由海灘的巨浪沖刷而成。然後走在沙地上，\n"
"卻感覺從腳心傳來陣陣熱氣，似乎著沙地下面蘊藏著什麼東西。\n"
);
        set("exits", ([ 
                "west"    : __DIR__"haitan", 
                "north"   : __DIR__"haitan1", 
                "south"   : __DIR__"haitan2", 
                "east"    : __DIR__"guanmucong", 
        ]));


        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/chihuoshe");

        setup();
}
