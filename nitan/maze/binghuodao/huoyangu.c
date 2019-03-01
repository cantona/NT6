inherit __DIR__"binghuodao";

void create()
{
        set("short", "火燄谷");
        set("long",
"火燄谷內地動山搖，似乎從未平靜過。不遠處無數大小火山正\n"
"爭先恐後的噴發著，誰也不肯停下的樣子。這裡熱氣騰騰，令人異\n"
"常難受，如果說還有生物的話，那肯定是經過千萬年進化的精怪。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"huoyangu2", 
                "north"   : __DIR__"xiagu2",
                "south"   : __DIR__"huoyanshiqiao",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huohu");               
        setup();
}
