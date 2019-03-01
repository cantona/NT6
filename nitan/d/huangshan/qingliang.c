// Room: /d/huangshan/qingliang.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "清涼台");
        set("long", @LONG
這乃黃山觀日出的所在，每天清晨，當人登上三面凌空的危巖向北
海遠眺，只見“白雲倒海忽平舖，點點螺髻時有無”，巍峨的群峰大都
淹沒在雲海之中。接著天際的魚肚白變成了五彩瑰麗的朝霞，雲層中射
出的紅光越來越亮，直到那輪火球沖破雲海，騰空而出。久久地讓人回
味。
LONG
        );
        set("exits", ([ 
                "northwest" : __DIR__"diezhang",
                "northeast" : __DIR__"feilong",
                "southup"   : __DIR__"shizi",
                "westup"    : __DIR__"qingliangf",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -1000);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}