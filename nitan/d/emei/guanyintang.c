inherit ROOM;

void create()
{
        set("short", "觀音堂");
        set("long", @LONG
觀音堂高踞坡崗近臨危崖，環境幽靜，四周樹木蓊鬱，悦目賞心。
傳説入山於此，解脱塵凡；出山於此，解脱險阻，又故名解脱庵。進
山的人在此焚香洗心，入山方可化險為夷步步平安。這裏東下可達伏
虎寺，西上行約二里可到歸雲閣。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"jietuopo",
                "westup"    : __DIR__"guiyunge",
        ]));
        set("outdoors", "emei");
        set("no_clean_up", 0);
        set("coor/x", -410);
        set("coor/y", -230);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}