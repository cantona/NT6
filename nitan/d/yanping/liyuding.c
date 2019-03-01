// Room: /d/yanping/liyuding.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "鯉魚頂");
        set("long", @LONG
鯉魚頂延綿江畔，其頭部峻峭如梭，直指江心，如鯉魚逆水，波濤
湍急，回流傳響不絕。山頂一座實心八層石塔，與對江九峰山的西塔遙
遙相對。
LONG );
        set("exits", ([
                "southup"   : __DIR__"dongta",
                "northeast" : __DIR__"guandao3",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}