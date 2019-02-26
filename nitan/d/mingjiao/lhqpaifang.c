//LHQPAIFANG.C

inherit ROOM;

void create()
{
    set("short", "烈火旗牌坊");
        set("long", @LONG
這裏是崑崙山南麓的一片開闊地，四周山崖環抱，青木遮天，正
對路中的是一座大紅牌坊。穿過牌坊，是一片紅磚紅瓦，遍插鑲紅團
龍旗，路邊齊齊站立兩排教眾，整個山谷中好似烈焰蒸騰，紅霧遍野，
實在是江湖中一般門派所沒有的壯觀景象。由此向東北折轉，大路直
通鋭金旗；由此向西北而行，則為巨木旗。三旗承犄角鼎立之勢，以
鞏固明教外圍。
LONG );
        set("exits", ([
                "northeast" : __DIR__"torjq1",
                "northwest" :__DIR__"tojmq1",
                "northup"   : __DIR__"lhqmen",
                "southdown" : __DIR__"shanlu4",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}