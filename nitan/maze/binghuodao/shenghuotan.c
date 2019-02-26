inherit __DIR__"binghuodao";

void create()
{
        set("short", "神火壇");
        set("long",
"這裏是一處寬闊的祭台，祭台中間有一根石柱，上面寫着鮮紅\n"
"的三個大字“神火台”，祭台四周矗立着四根石柱，上面雕刻着各種\n"
"火焰的模樣。據説在這裏汲取實戰體會（jiqu）能獲得更多收穫。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"guanmulin2", 
                "southwest"   : __DIR__"shenmihuodong2",
        ]));
        setup();
}
