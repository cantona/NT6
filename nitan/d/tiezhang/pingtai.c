#include <ansi.h>

inherit ROOM;
string look_ditu();

void create()
{
        set("short", "山間平台");
        set("long", @LONG
這裡是山間的一塊平地。山勢在這裡開始分支，矗立在面前的有五座高
聳入雲的山峰，型似五指，“鐵掌山”之名由此而得。五峰雖同處此山，但
拇指峰之雄偉，食指峰之險峻，中指峰之高聳，無名峰之奇麗，小指峰之秀
美，則各有特色，各擅勝場。在平台一側的大石上，刻著一副地圖(map)。
LONG );
        set("item_desc", ([ 
                "map" : (: look_ditu :),
        ]));

        set("exits", ([ 
                "westup" : __DIR__"shanlu-5",
                "northeast" : __DIR__"shangu-1",
                "eastup" : __DIR__"sslu-1",
                "southdown" : __DIR__"shanlu-4",
                "northwest" : __DIR__"hclu",
                "northup" : __DIR__"shanlu-6",
        ]));

        set("objects", ([ 
                __DIR__"npc/huiyi" : 3,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        
}

string look_ditu()
{
    return
    "\n"
  WHT "\n\n\n    ################################\n"
            "    ##                            ##\n"
            "    ##           中指峰           ##\n"
            "    ##             ｜             ##\n"
            "    ##     無名峰  ｜  食指峰     ##\n"
            "    ##        ＼   ｜   ／        ##\n"
            "    ##          ＼ ｜ ／          ##\n"
            "    ##  小指峰──平台──拇指峰  ##\n"
            "    ##                            ##\n"
            "    ################################\n\n\n\n\n" NOR;
    "\n";
}