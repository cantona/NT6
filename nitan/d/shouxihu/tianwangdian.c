// Room: /yangzhou/tianwangdian.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","天王殿");
        set("long",@LONG
山門內為天王殿，面南正中，五架樑。中設佛龕，端坐彌勒佛，龕
前有楹聯(lian)。背立護法韋陀。兩廂列彩塑四大天王：東廂立東方持
國天王、南方增長天王，西廂立西方廣目天王、北方多聞天王。
LONG );
        set("item_desc", ([
                "lian" : "
        大腹能容容天下難容之事

        慈顏常笑笑世間可笑之人
\n"
        ]));
        set("objects", ([
                "/d/hangzhou/npc/shami" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"yongdao",
                "south" : __DIR__"shanmen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 150);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}