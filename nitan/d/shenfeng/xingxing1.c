inherit ROOM;

void create()
{
        set("short", "星星峽");
        set("long", @LONG
遠處出現了一抹崗巒。轉眼之間，石壁越來越近，一字排
開，直伸出去，山石間雲霧□漫，似乎其中別有天地，再走近
時忽覺峭壁中間露出一條縫來，沿山道直走進去，便是甘肅和
回疆之間的交通孔道星星峽。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"xingxing2",
                  "east" : __DIR__"guandao4",
        ]));
        set("objects", ([
                __DIR__"npc/seller" : 1,
        ]));
        setup();
        replace_program(ROOM);
}