inherit __DIR__"binghuodao";

void create()
{
        set("short", "神火壇");
        set("long",
"這裡是一處寬闊的祭台，祭台中間有一根石柱，上面寫著鮮紅\n"
"的三個大字“神火台”，祭台四周矗立著四根石柱，上面雕刻著各種\n"
"火燄的模樣。據說在這裡汲取實戰體會（jiqu）能獲得更多收獲。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"guanmulin2", 
                "southwest"   : __DIR__"shenmihuodong2",
        ]));
        setup();
}
