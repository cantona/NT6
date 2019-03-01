inherit ROOM;

void create()
{
        set("short", "睹光台");
        set("long", @LONG
這裡是看日出、雲海、佛光、神燈之地。台下深崖萬丈陡徹無底，
雲遮霧掩。極目四望，數百裡外的大小雪山皆歷歷在目。金頂雲海，
迷迷茫茫，籠罩四野，遠接天際。雲海輕盪時，你在金頂，腳踏白雲，
大有飄飄欲仙之感；當雲濤迅猛湧來時整個金頂都似在向前浮動，令
人有乘舟欲風之意。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/bei" : 1,
        ]));
        set("outdoors", "emei");
        set("exits", ([
                "northeast" : __DIR__"huacangan",
                "northwest" : __DIR__"woyunan",
                "south" : __DIR__"dgtsheshenya", 
        ]));
        set("coor/x", -570);
        set("coor/y", -330);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}