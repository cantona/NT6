inherit BUILD_ROOM;

void create()
{
        set("short", "老龍頭");
        set("long", @LONG
老龍頭是萬里長城最東端。澄海樓巍峨高踞城頭，樓上“雄襟萬里”的
橫匾居高臨下，直俯大海。自澄海樓築有一石城逐級而下伸入大海，站在石
城終端樓平台上四眺，海天一色，無邊無際，氣象萬千。
LONG );
        set("exits", ([
                "northwest" : __DIR__"shanhaiguan",
                "southwest" : "/d/beijing/road3",
        ]));

        set("outdoors", "guanwai");
        set("coor/x", 3950);
	set("coor/y", 9110);
	set("coor/z", 0);
	setup();
}
