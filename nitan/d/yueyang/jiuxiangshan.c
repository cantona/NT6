// Room: /d/yueyang/jiuxiangshan.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "酒香山");
        set("long", @LONG
傳說山上有美酒，喝了能成仙。想長生不老的漢武帝聽說後，便派
文士欒巴到君山求酒。酒求回後，便被東方朔給搶先喝了，後來鬧出一
場笑話。大抵是漢武帝大怒，欲斬東方朔。東方朔辯稱，如自己被賜而
死，則仙酒無長生功效，自然不是真仙酒；仙酒既然不真則朔不當死。
漢武帝兩難之間，無法可施。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"jiuxiangting",
                "west"  : __DIR__"yangyaozai",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bai-shijing" : 1,
        ]));
        set("coor/x", -1780);
        set("coor/y", 2290);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}