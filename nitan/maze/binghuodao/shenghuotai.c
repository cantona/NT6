inherit __DIR__"binghuodao";

void create()
{
        set("short", "聖火台");
        set("long",
"這裏是一處寬闊的祭台，祭台中間有一根石柱，上面寫着鮮紅\n"
"的三個大字“升火台”，祭台四周矗立着四根石柱，上面雕刻着各種\n"
"奇怪的模樣。據説在這裏研究技能可獲得更多研究次數。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"jitan", 
                "south"   : __DIR__"shenmihuodong",
                "west"    : __DIR__"huoyangu2",
        ]));
        setup();
}
