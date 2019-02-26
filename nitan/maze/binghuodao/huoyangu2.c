inherit __DIR__"binghuodao";

void create()
{
        set("short", "火焰谷");
        set("long",
"火焰谷內地動山搖，似乎從未平靜過。不遠處無數大小火山正\n"
"爭先恐後的噴發着，誰也不肯停下的樣子。這裏熱氣騰騰，令人異\n"
"常難受，如果説還有生物的話，那肯定是經過千萬年進化的精怪。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"shenghuotai", 
                "west"   : __DIR__"huoyangu",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huohu");               
        setup();
}
