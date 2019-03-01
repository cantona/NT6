// /d/beihai/jingqing.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "靜清齋");
        set("long", @LONG
北岸之鏡清齋（後改名為靜心齋）為一精美之園中園，是清太子來
遊時之居所，入門為荷池，池北為堂，堂後臨山池，左右皆峰巒巖洞，
往昔有飛瀑流水往還縈回。池中有敞閣三間，名沁泉廊，廊後有山石回
抱，為乾隆時迭石之精品。遍布之太湖石山景，玲瓏剔透，與隱現在翠
竹花木中的亭台軒橋互相輝映，景色幽雅。
LONG
        );

        set("exits", ([
                "east"      : __DIR__"houmen",
                "southwest" : __DIR__"xitian",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -170);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}