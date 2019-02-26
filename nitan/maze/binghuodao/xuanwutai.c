inherit __DIR__"binghuodao";

void create()
{
        set("short", "玄武台");
        set("long",
"這裏是一處寬闊的祭台，祭台中間有一根石柱，上面寫着鮮紅\n"
"的三個大字“玄武台”，祭台四周矗立着四根石柱，上面雕刻着玄武\n"
"神獸的模樣。據説在這裏冥思（reflect）能獲得更多收穫。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"bingfenggu2", 
                "north"   : __DIR__"shenmibingdong",
                "south"   : __DIR__"jitan",
        ]));
        setup();
}
