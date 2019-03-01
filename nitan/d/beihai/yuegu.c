// /d/beihai/yuegu.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "閱古樓");
        set("long", @LONG
閱古樓平面為一馬蹄形，有廊二十五楹，左右圍抱。內有蟠龍升天
式樓梯。壁砌三希堂法帖 (tie)石刻。山坡上點綴假山、庭閣，高下曲
折有致，如畝鑒室、煙雲盡態亭、水精域、甘露殿、蟠青室、揖山亭等。
LONG
        );
        set("item_desc", ([
                "tie" : "王羲之《快雪時晴帖》，王獻之《中秋帖》，王徇《迫遠帖》\n",
        ]));
        set("exits", ([
                "southup"   : __DIR__"qingxiao",
                "northeast" : __DIR__"yilan",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}