inherit __DIR__"binghuodao";

void create()
{
        set("short", "玄武台");
        set("long",
"這裡是一處寬闊的祭台，祭台中間有一根石柱，上面寫著鮮紅\n"
"的三個大字“玄武台”，祭台四周矗立著四根石柱，上面雕刻著玄武\n"
"神獸的模樣。據說在這裡冥思（reflect）能獲得更多收獲。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"bingfenggu2", 
                "north"   : __DIR__"shenmibingdong",
                "south"   : __DIR__"jitan",
        ]));
        setup();
}
