inherit ROOM;

void create()
{
        set("short", "花徑");
        set("long", @LONG 
這是一條種滿了各色梅花的花徑。小徑兩邊梅花飄香，梅
萼生寒。悠然而賞鑒，梅枝蜿蜒，梅幹崎嶇，古樸飄逸，兼而
有之。梅枝幹以枯殘醜拙為貴，梅花梅萼以繁密濃聚為尚，此
處之景，可謂得矣。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "east"  : __DIR__"qianyuan",
                    "up"  : __DIR__"feihua",  
        ]));
        set("objects", ([
               "/clone/quarry/he2" : 1,
               __DIR__"obj/mei" : 4,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
