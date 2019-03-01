// /d/beihai/wulong.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "五龍亭");
        set("long", @LONG
這裡是闡福寺前之五龍亭，亭子伸入水中，五亭俱為方形，前後錯
落布置。中亭名龍澤，重檐下方上恩賜，左面澄祥亭為重檐，滋香亭為
單檐；右面湧瑞亭，浮翠亭與左面相同。五亭皆綠琉璃瓦頂，黃瓦剪邊，
檐下樑枋施小點金旋子彩畫，絢麗多彩。
LONG
        );
        set("exits", ([
                "west" : __DIR__"xiaolu2",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}