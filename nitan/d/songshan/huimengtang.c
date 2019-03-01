// Room: /d/songshan/huimengtang.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "會盟堂");
        set("long", @LONG
這裡原來是峻極禪院的大雄寶殿，自五岳劍派百年前在此歃血為盟
以來，這裡就成了五岳劍派中樞所在了。堂上正中放著一張黃綢太師敞
椅，那是盟主的寶座。兩邊雁形排列著泰、華、衡、恆的青呢、白緞、
紅羅、黑綾座椅，椅後插著各派的五色旗。
LONG );
        set("exits", ([
                "south" : __DIR__"zhongmen",
                "north" : __DIR__"jianchi",
        ]));
        set("objects", ([
                CLASS_D("songshan")+"/zuo" : 1,
        ]));
        set("coor/x", -20);
        set("coor/y", 890);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}